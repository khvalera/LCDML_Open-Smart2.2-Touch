/* ===================================================================== *
 * Dynamic content                                                       *
 * ===================================================================== */

uint8_t g_dynParam = 100;  // when this value comes from an EEPROM, load it in setup
                           // at the moment here is no setup function (To-Do)

// =====================================================================
void mDyn_para(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos()) {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny()) {
      if (LCDML.BT_checkEnter()) {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0) {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          display.fillRect(0, _LCDML_FONT_H * (LCDML.MENU_getCursorPos()), 220, 18, RED);
          LCDML.MENU_disScroll();
        } else {
          // enable the normal menu scroll function
          display.fillRect(0, _LCDML_FONT_H * (LCDML.MENU_getCursorPos()), 220, 18, BLUE);
          LCDML.MENU_enScroll();
        }

        // do something
        // ...
        LCDML.BT_resetEnter();
        // This check have only an effect when MENU_disScroll is set
      } else if (LCDML.BT_checkUp()) {
        display.fillRect(0, _LCDML_FONT_H * (LCDML.MENU_getCursorPos()), 220, 18, RED);
        g_dynParam++;
        LCDML.BT_resetUp();
        // This check have only an effect when MENU_disScroll is set
      } else if (LCDML.BT_checkDown()) {
        display.fillRect(0, _LCDML_FONT_H * (LCDML.MENU_getCursorPos()), 220, 18, RED);
        g_dynParam--;
        LCDML.BT_resetDown();
      }
    } else {
      display.fillRect(0, _LCDML_FONT_H * (LCDML.MENU_getCursorPos()), 220, 18, BLUE);
    }
  }

  char buf[20];
  sprintf(buf, "dynValue: %d", g_dynParam);

  display.setCursor(12, _LCDML_FONT_H * (line));
  display.println(buf);
}
