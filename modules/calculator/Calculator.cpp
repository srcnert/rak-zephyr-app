#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "Calculator.h"

Calculator::Calculator() {
    printk("Creating calculator object!\r\n");
}

int Calculator::add(int a, int b) {
    return a + b;
}

int Calculator::multiply(int a, int b) {
    return a * b;
}