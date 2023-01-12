void setRgbColor(int red_pin_val, int green_pin_val, int blue_pin_val, int led_param) {
  if (led_param == 1) {
    analogWrite(un_r_pin_led, red_pin_val);
    analogWrite(un_g_pin_led, green_pin_val);
    analogWrite(un_b_pin_led, blue_pin_val);
  } else if (led_param == 2) {
    analogWrite(dos_r_pin_led, red_pin_val);
    analogWrite(dos_g_pin_led, green_pin_val);
    analogWrite(dos_b_pin_led, blue_pin_val);
  } else if (led_param == 3) {
    analogWrite(tre_r_pin_led, red_pin_val);
    analogWrite(tre_g_pin_led, green_pin_val);
    analogWrite(tre_b_pin_led, blue_pin_val);
  } else if (led_param == 4) {
    analogWrite(quat_r_pin_led, red_pin_val);
    analogWrite(quat_g_pin_led, green_pin_val);
    analogWrite(quat_b_pin_led, blue_pin_val);
  }
}

void setRedColorRGB(int led_param) {
  setRgbColor(255, 0, 0, led_param);
}

void setOrangeColorRGB(int led_param) {
  setRgbColor(255, 165, 0, led_param);
}

void setGreenColorRGB(int led_param) {
  setRgbColor(0, 255, 0, led_param);
}

void setBlueColorRGB(int led_param) {
  setRgbColor(0, 0, 255, led_param);
}

void setMagentaColorRGB(int led_param) {
  setRgbColor(255, 0, 255, led_param);
}

void setYellowColorRGB(int led_param) {
  setRgbColor(255, 255, 0, led_param);
}

void setCyanColorRGB(int led_param) {
  setRgbColor(0, 255, 255, led_param);
}

void setWhiteColorRGB(int led_param) {
  setRgbColor(255, 255, 255, led_param);
}
