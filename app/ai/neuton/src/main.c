/**
 * @file main.c
 * @author rakwireless.com
 * @brief This example shows how to use the RAK1904 and a Neuton AI model. The default model determins the orientation
 * of the board with the following classes (Note: RAK1904 is installed on the bottom side of the board (Slot D)):
 * 			Class 0 - board is sitting flat on the table
 * 			Class 1 - USB connector is facing up
 * 			Class 2 - board is upside down (bottom if facing up)
 * 			Class 3 - bottom edge of PCB is facing up (side with headers on the base board)
 * @note
 * 		1) The RUNTIME define determins if the code is running to gather data to train a model, or running the actual model
 * 				See the  MODELBUILD section for details on creating a model
 * 		2) The model downloaded from Neuton should be placed into the neuton-ai folder (copy and replace the two sub-folders)
 * 		3) The default model was created with a window size of 50 (which is probably much larger than needed!)
 *
 * @version 1.0
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define RUNTIME // RUNTIME or MODELBUILD

/* MODELBUILD :
For model building you will need to save the output from the serial port to a file for
	each "motion" that the model will detect.

	1. Start moving the board in the desired motion, then run the command below
		For Linux/MacOS run the command below to save to a file (you will need to adjust to the correct port & filename):
			(stty speed 115200 >/dev/null && cat) </dev/cu.usbmodem101 | tee RAK1904_UP-DOWN.log
		For Windows:
			TBD

	2. Once you have each motion saved to a file append the class to each line of all files (see example model_data)

	3. combine all the files into a single file (see RAK1904_data.csv example)

	4. Upload this file to Neuton to create your model
*/

#if defined(RUNTIME)
#include <neuton/neuton.h>
#endif

#if !DT_HAS_COMPAT_STATUS_OKAY(st_lis3dh)
#error "No st,lis3dh compatible node found in the device tree"
#endif

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(st_lis3dh);
	int rc;

	printf("Check Device ready\n");
	if (!device_is_ready(dev)) {
		printf("Device %s is not ready :( \n", dev->name);
		return 0;
	}

#if defined(RUNTIME)
	/* Set-up Neuton */
	neuton_nn_setup();
	printf("Neuton input window size %d\n", neuton_nn_input_window_size());
	printf("neuton_nn_uniq_inputs_num %d\n", neuton_nn_uniq_inputs_num());
#endif

	while (1) {
		struct sensor_value accel[3];
		rc = sensor_sample_fetch(dev);
		if (rc == 0) {
			rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);
		}

		if (rc != 0) {
			printf("RAK1904(LIS3DH): failed: %d\n", rc);
			break;
		}

#if defined(MODELBUILD)
		printk("%.2f,%.2f,%.2f\r\n", sensor_value_to_double(&accel[0]),
		       sensor_value_to_double(&accel[1]), sensor_value_to_double(&accel[2]));
#endif

#if defined(RUNTIME)
		neuton_input_t neuton_raw_inputs[] = {sensor_value_to_double(&accel[0]),
						      sensor_value_to_double(&accel[1]),
						      sensor_value_to_double(&accel[2])};

		/* Feed and prepare raw inputs for the model inference */
		neuton_input_features_t *p_input =
			neuton_nn_feed_inputs(neuton_raw_inputs, 3); // model expects 3 inputs

		/* Run inference */
		if (p_input) {
			neuton_u16_t predicted_target;
			const neuton_output_t *p_probabilities;
			/* Run Neuton model inference */
			neuton_i16_t targets_num = neuton_nn_run_inference(
				p_input, &predicted_target, &p_probabilities);
			if (targets_num > 0) {
				printf("Predicted target %d with probability %d\r\n",
				       predicted_target, p_probabilities[predicted_target]);
				/* Uncomment to show all the probabilities! */
				/*
				printf("\t");
				for (size_t i = 0; i < targets_num; i++)
				{
					printf("%d ",p_probabilities[i]);
				}
					printf("\r\n");
				*/
			}
		}
#endif
	}
	return 0;
}
