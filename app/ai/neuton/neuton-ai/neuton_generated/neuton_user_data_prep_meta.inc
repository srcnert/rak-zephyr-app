/* 2025-10-12T21:56:04.597120 */

/* ----------------------------------------------------------------------
Copyright (c) 2022-2025 Neuton.AI, Inc.
*
The source code and its binary form are being made available on the following terms:
Redistribution, use, and modification are permitted provided that the following
conditions are met:
*
1. Redistributions of source code and/or its binary form must retain the above copyright notice,
* this list of conditions (and the disclaimer) either in the body of the source code or in
* the documentation and/or other materials provided with the distribution of the binary form, as
applicable.
*
2. The name of the copyright holder may not be used to endorse or promote products derived from this
* source code or its binary form without specific prior written permission of Neuton.AI, Inc.
*
3. Disclaimer. THIS SOURCE CODE AND ITS BINARY FORM ARE PROVIDED BY THE COPYRIGHT HOLDER "AS IS".
* THE COPYRIGHT HOLDER HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS
* OF THIRD PARTIES; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE OR ITS BINARY FORM, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------- */

/** Defines input(also used for LAG) features MIN scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MIN[] =
{ -9.7700005, -11.0699997, -10.0400000 };

/** Defines input(also used for LAG) features MAX scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MAX[] =
{ 11.0299997, 9.9600000, 11.1099997 };

/** Defines feature extraction masks used as neuton_nn_features_mask_t,
 *  64 bit for one unique input feature, @ref neuton_nn_features_mask_t to see bitmask
 */
static const neuton_u64_t FEATURES_EXTRACTION_MASK[] =
{ 0x800b00000000, 0x401700000000, 0x411f00000000 };

/** Defines extracted features MIN scaling factor
 */
static const neuton_feature_t EXTRACTED_FEATURES_SCALE_MIN[] =
{ -9.7700005, -9.5000000, -9.5747967, 0.0000000, -11.0699997, -9.9200001,
 0.0000000, 0.0000000, 0.0000000, -10.0400000, -9.5799999, 0.0000000,
 -9.6818027, 0.0000000, 0.0400000, 0.0324000 };

/** Defines extracted features MAX scaling factor
 */
static const neuton_feature_t EXTRACTED_FEATURES_SCALE_MAX[] =
{ 10.8800001, 11.0299997, 10.9261990, 0.2306122, 9.5000000, 9.9600000,
 19.0699997, 8.4952507, 10.1082039, 10.1099997, 11.1099997, 6.6700001,
 10.8087997, 2.7804008, 10.8147697, 10.8087997 };
