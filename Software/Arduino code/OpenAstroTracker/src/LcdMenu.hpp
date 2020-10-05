#ifndef _LCDMENU_HPP_
#define _LCDMENU_HPP_

#include <Arduino.h>
#if HEADLESS_CLIENT == 0
#include <LiquidCrystal.h>
#endif
#include "../Configuration_adv.hpp"

// A single menu item (like RA, HEAT, POL, etc.)
// The ID is just a number, it has no relevance for the order of the items
// The display is what is shown on the menu.
class MenuItem {
  const char* _display;     // What to display on the screen
  byte _id;             // The ID of the menu item
public:
  MenuItem(const char* display, byte id) {
    _display = display;
    _id = id;
  }

  const char* display() {
    return _display;
  }

  byte id() {
    return _id;
  }
};

// Class that drives the LCD screen with a menu
// You add a string and an id item and this class handles the display and navigation
class LcdMenu {
public:
  // Create a new menu, using the given number of LCD display columns and rows
  LcdMenu(byte cols, byte rows, int maxItems);

  // Find a menu item by its ID
  MenuItem* findById(byte id);

  // Add a new menu item to the list (order matters)
  void addItem(const char* disp, byte id);

  // Get the currently active item ID
  byte getActive();

  // Set the active menu item
  void setActive(byte id);

  // Pass thru utility function
  void setCursor(byte col, byte row);

  // Set and get the brightness of the backlight
  void setBacklightBrightness(int level, bool persist = true);
  int getBacklightBrightness();

  // Pass thru utility function
  void clear();

  // Go to the next menu item from currently active one
  void setNextActive();

  // Update the display of the LCD with the current menu settings
  // This iterates over the menu items, building a menu string by concatenating their display string.
  // It also places the selector arrows around the active one.
  // It then sends the string to the LCD, keeping the selector arrows centered in the same place.
  void updateDisplay();

  // Print a string to the LCD at the current cursor position, substituting the special arrows and padding with spaces to the end
  void printMenu(String line);

  // Print a character at a specific position
  void printAt(int col, int row, char ch);

private:
  // Print a single character at the current cursor location and advance cursor by one. Substitutes special chars.
  void printChar(char ch);

private:
#if HEADLESS_CLIENT == 0
  LiquidCrystal _lcd;   // The LCD screen that we'll display the menu on
  MenuItem** _menuItems;  // The first menu item (linked list)
  byte _numMenuItems;
  byte _activeMenuIndex;
  byte _longestDisplay;   // The number of characters in the longest menu item
  byte _columns;          // The number of columns in the LCD display
  byte _activeRow;        // The row that the LCD cursor is on
  byte _activeCol;        // The column that the LCD cursor is on
  String _lastDisplay[2]; // The last string that was displayed on each row
  int _brightness;

  byte _degrees = 1;
  byte _minutes = 2;
  byte _leftArrow = 3;
  byte _rightArrow = 4;
  byte _upArrow = 5;
  byte _downArrow = 6;
  byte _tracking = 7;
  byte _noTracking = 0;


  // The special character bitmaps
  static byte RightArrowBitmap[8];
  static byte LeftArrowBitmap[8];
  static byte UpArrowBitmap[8];
  static byte DownArrowBitmap[8];
  static byte DegreesBitmap[8];
  static byte MinutesBitmap[8];
  static byte TrackingBitmap[8];
  static byte NoTrackingBitmap[8];

#endif
};

#endif