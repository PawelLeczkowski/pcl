//
// Created by pawel on 03.01.2026.
//

#ifndef PCL_PCL_UNICODE_H
#define PCL_PCL_UNICODE_H


#include "pcldef.h"

/**
 * Initializes new unicode screen
 *
 * @param console
 * @return initialized screen
 */
struct UnicodeScreen* initunicode(struct Console *console);

/**
 * Sets echo struct.
 * Echoed characters will be visible after refresh
 *
 * @param console pointer to struct Console
 * @param unicodeEcho pointer to struct UnicodeScreen. Only that struct gets echoed character.
 * @return 0 if eveything went well otherwise returns -1
 */
int setunicodeecho(struct Console* console, struct UnicodeScreen* unicodeEcho);

/**
 * Unsets echo struct
 *
 * @param console pointer to struct Console
 * @return 0 if eveything went well otherwise returns -1
 */
int unsetunicodeecho(struct Console* console);

/**
 * Sets cursor style
 *
 * @param unicode pointer to struct ScreenAscii
 * @param style one of 6 predefined styles, can be BLINKING_BLOCK, STEADY_BLOCK, BLINKING_UNDERLINE, STEADY_UNDERLINE, BLINKING_BAR or STEADY_BAR
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL<br>
 * (-2) style parameter is unknown
 */
int setcursorstyleunicode(struct UnicodeScreen *unicode, int style);

/**
 * Sets cursor style to default (BLINKING_BAR)
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetcursorstyleunicode(struct UnicodeScreen *unicode);

/**
 * Shows cursor in unicode window
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
*/
int showcursorunicode(struct UnicodeScreen *unicode);

/**
 * Hides cursor in unicode window
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
*/
int hidecursorunicode(struct UnicodeScreen *unicode);

/**
 * Sets font bold property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int setfontboldunicode(struct UnicodeScreen *unicode);

/**
 * Unsets font bold property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetfontboldunicode(struct UnicodeScreen *unicode);

/**
 * Returns font bold property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return bold property (TRUE or FALSE) if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int getfontboldunicode(struct UnicodeScreen *unicode);

/**
 * Sets font dim property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int setfontdimunicode(struct UnicodeScreen *unicode);

/**
 * Unsets font dim property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetfontdimunicode(struct UnicodeScreen *unicode);

/**
 * Returns font dim property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return dim property (TRUE or FALSE) if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int getfontdimunicode(struct UnicodeScreen *unicode);

/**
 * Sets font italic property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int setfontitalicunicode(struct UnicodeScreen *unicode);

/**
 * Unsets font italic property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetfontitalicunicode(struct UnicodeScreen *unicode);

/**
 * Returns font italic property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return italic property (TRUE or FALSE) if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int getfontitalicunicode(struct UnicodeScreen *unicode);

/**
 * Sets font underline property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int setfontunderlineunicode(struct UnicodeScreen *unicode);

/**
 * Unsets font underline property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetfontunderlineunicode(struct UnicodeScreen *unicode);

/**
 * Returns font underline property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return underline property (TRUE or FALSE) if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int getfontunderlineunicode(struct UnicodeScreen *unicode);

/**
 * Sets font blinking property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int setfontblinkingunicode(struct UnicodeScreen *unicode);

/**
 * Unsets font blinking property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetfontblinkingunicode(struct UnicodeScreen *unicode);

/**
 * Returns font blinking property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return blinking property (TRUE or FALSE) if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int getfontblinkingunicode(struct UnicodeScreen *unicode);

/**
 * Sets font strikethrough property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int setfontstrikethroughunicode(struct UnicodeScreen *unicode);

/**
 * Unsets font strikethrough property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetfontstrikethroughunicode(struct UnicodeScreen *unicode);

/**
 * Returns font strikethrough property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return strikethrough property (TRUE or FALSE) if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int getfontstrikethroughunicode(struct UnicodeScreen *unicode);

/**
 * Sets font doubleunderline property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int setfontdoubleunderlineunicode(struct UnicodeScreen *unicode);

/**
 * Unsets font doubleunderline property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int unsetfontdoubleunderlineunicode(struct UnicodeScreen *unicode);

/**
 * Returns font doubleunderline property
 *
 * @param unicode pointer to struct ScreenAscii
 * @return doubleunderline property (TRUE or FALSE) if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int getfontdoubleunderlineunicode(struct UnicodeScreen *unicode);

/**
 * Sets foreground color to specified value
 *
 * @param unicode pointer to struct ScreenAscii
 * @param red red
 * @param green green
 * @param blue blue
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 * (-2) red parameter is greater than 255
 * (-3) green parameter is greater than 255
 * (-4) blue parameter is greater than 255
 */
int setforegroundcolorunicode(struct UnicodeScreen *unicode, unsigned int red, unsigned int green, unsigned int blue);

/**
 * Sets background color to specified value
 *
 * @param unicode pointer to struct ScreenAscii
 * @param red red
 * @param green green
 * @param blue blue
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 * (-2) red parameter is greater than 255
 * (-3) green parameter is greater than 255
 * (-4) blue parameter is greater than 255
 */
int setbackgroundcolorunicode(struct UnicodeScreen *unicode, int red, int green, int blue);

/**
 * Sets foreground color to default value
 *
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int clearforegroundcolorunicode(struct UnicodeScreen *unicode);

/**
 * Sets background color to default value
 *
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int clearbackgroundcolorunicode(struct UnicodeScreen *unicode);

/**
 * Prints string on cursor position. Changes cursor position
 *
 * @param unicode pointer to struct Ascii
 * @param string input
 *
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 * (-1) string parameter is NULL
 */
int setstringunicode(struct UnicodeScreen *unicode, wchar_t* string);

/**
 * Prints string on cursor position. Do not changes cursor position
 *
 * @param unicode pointer to struct Ascii
 * @param string input
 * @param row row number
 * @param col column number
 *
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL<br>
 * (-2) row parameter is lower than zero <br>
 * (-3) col parameter is lower than zero <br>
 * (-4) string parameter is NULL<br>
 * (-5) row parameter is greater than unicode height <br>
 * (-6) col parameter is greater than unicode width
 */
int setstringcursorunicode(struct UnicodeScreen *unicode, wchar_t* string, int row, int col);

/**
 * Clears unicode
 *
 * @param unicode pointer to struct Ascii
 */
int clearunicode(struct UnicodeScreen *unicode);

/**
 * Fills unicode with specified char
 *
 * @param unicode pointer to struct Ascii
 * @param c char to be filled
 * @param foregroundRed foreground color red value
 * @param foregroundGreen foreground color green value
 * @param foregroundBlue foreground color blue value
 * @param backgroundRed backround color red value
 * @param backgroundGreen backround color green value
 * @param backgroundBlue backround color blue value
 * @param bold is text bold
 * @param dim is text dim
 * @param italic is text italic
 * @param underline is text underline
 * @param blinking is text blinking
 * @param strikethrough is text strikethrough
 * @param doubleunderline is text doubleunderline
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL<br>
 * (-2) foreground red parameter is greater than 255<br>
 * (-3) foreground green parameter is greater than 255<br>
 * (-4) foreground blue parameter is greater than 255<br>
 * (-5) background red parameter is greater than 255<br>
 * (-6) background green parameter is greater than 255<br>
 * (-7) background blue parameter is greater than 255<br>
 * (-8) bold parameter is not a valid BOOL vaiable<br>
 * (-9) dim parameter is not a valid BOOL vaiable<br>
 * (-10) italic parameter is not a valid BOOL vaiable<br>
 * (-11) underline parameter is not a valid BOOL vaiable<br>
 * (-12) blinking parameter is not a valid BOOL vaiable<br>
 * (-13) strikethrough parameter is not a valid BOOL vaiable<br>
 * (-14) doubleunderline parameter is not a valid BOOL vaiable
 */
int fillunicode(struct UnicodeScreen *unicode, wchar_t *c,
	unsigned int foregroundRed, unsigned int foregroundGreen, unsigned int foregroundBlue,
	unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
	BOOL bold, BOOL dim, BOOL italic, BOOL underline, BOOL blinking, BOOL strikethrough, BOOL doubleunderline);

/**
 * Fills unicode with specified char
 *
 * @param unicode pointer to struct Ascii
 * @param c char to be filled
 *
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL
 */
int fillcharunicode(struct UnicodeScreen *unicode, wchar_t *c);

/**
 * Sets 2d array on specified location. Do not changes cursor position
 *
 * @param unicode pointer to struct Ascii
 * @param array array to write
 * @param row top-left array position of array in unicode
 * @param col top-left array position of array in unicode
 * @param width array height
 * @param height array wwidth
 *
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL<br>
 * (-2) array parameter is NULL<br>
 * (-3) height parameter equals 0<br>
 * (-4) width parameter equals 0<br>
 */
int set2darrayunicode(struct UnicodeScreen *unicode, wchar_t* array, unsigned int row, unsigned int col, unsigned int width, unsigned int height);

/**
 * Sets cursor position
 *
 * @param unicode pointer to struct Ascii
 * @param row row number
 * @param col column number
 */
int setcursorpositionunicode(struct UnicodeScreen *unicode, unsigned int row, unsigned int col);

/**
 * Returns cursor position
 *
 * @param unicode pointer to struct Ascii
 * @param row row number
 * @param col column number
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL<br>
 * (-2) row parameter is NULL<br>
 * (-3) col parameter is NULL<br>
 */
int getcursorpositionunicode(struct UnicodeScreen *unicode, unsigned int *row, unsigned int *col);

/**
 * Prints unicode window
 *
 * @param console pointer to struct Console
 * @param unicode pointer to struct Ascii
 *
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) unicode parameter is NULL<br>
 * (-2) internal function error
 */
int refreshunicode(struct Console* console, struct UnicodeScreen* unicode);

/**
 * Returns unicode dimensions
 *
 * @param unicode pointer to structure unicode
 * @param width unicode width
 * @param height unicode height
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) width parameter is NULL<br>
 * (-2) height parameter is NULL<br>
 * (-3) unicode parameter is NULL
 */
int getdimensionsunicode(struct UnicodeScreen *unicode, unsigned int* width, unsigned int* height);

/**
 * Prints formatted string on cursor position. Changes cursor position.
 *
 * @param unicode pointer to struct Console
 * @param format format string
 * @param ... variables to format
 *
 * @return size of written string if eveything went well otherwise returns negative:<br>
 * (-1) console parameter is NULL<br>
 * (-2) format parameter is NULL<br>
 * (-3) format parameter is not a valid format string<br>
 * (-4) internal error<br>
 *
 * Possible standard tokens:<br>
 * %ull unsigned long long<br>
 * %ll long long<br>
 * %uh unsigned short<br>
 * %ud unsigned int<br>
 * %ul unsigned long<br>
 * %c char<br>
 * %h short<br>
 * %d int<br>
 * %l long<br>
 * %s string<br>
 * %% '%' character<br>
 * Possible styles:<br>
 * @<number>;<number>;<number>f foreground color<br>
 * @<number>;<number>;<number>b background color<br>
 * @b bold<br>
 * @rb remove bold<br>
 * @d dim<br>
 * @rd remove dim<br>
 * @i italic<br>
 * @ri remove italic<br>
 * @u underline<br>
 * @ru remove underline<br>
 * @l blinking<br>
 * @rl remove blinking<br>
 * @s strikethrough<br>
 * @rs remove strikethrough<br>
 * @uu doubleunderline<br>
 * @ruu remove doubleunderline<br>
 * @c clear all<br>
 * @@ at character
 */
int setstringformattedunicode(struct UnicodeScreen *unicode, wchar_t* format, ...);

/**
 * Prints formatted string on cursor position. Do not changes cursor position. See setstringformatted() for more information.
 *
 * @param unicode pointer to struct Console
 * @param format format string
 * @param row row number
 * @param col column number
 * @param ... variables to format
 *
 * @return size of written string if eveything went well otherwise returns negative:<br>
 * (-1) console parameter is NULL<br>
 * (-2) row parameter is lower than zero <br>
 * (-3) col parameter is lower than zero <br>
 * (-4) format parameter is NULL<br>
 * (-5) row parameter is greater than console height <br>
 * (-6) col parameter is greater than console width<br>
 * (-7) format parameter is not a valid format string<br>
 * (-8) internal error
 */
int setstringformattedcursorunicode(struct UnicodeScreen *unicode, int row, int col, wchar_t* format, ...);

/**
 * Sets char on cursor position. Changes cursor position. Allows to customize character.
 *
 * @param unicode pointer to structure console
 * @param c char to set
 * @param foregroundRed foreground color red value
 * @param foregroundGreen foreground color green value
 * @param foregroundBlue foreground color blue value
 * @param backgroundRed backround color red value
 * @param backgroundGreen backround color green value
 * @param backgroundBlue backround color blue value
 * @param bold is text bold
 * @param dim is text dim
 * @param italic is text italic
 * @param underline is text underline
 * @param blinking is text blinking
 * @param strikethrough is text strikethrough
 * @param doubleunderline is text doubleunderline
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) console parameter is NULL
 * (-2) foreground red parameter is greater than 255<br>
 * (-3) foreground green parameter is greater than 255<br>
 * (-4) foreground blue parameter is greater than 255<br>
 * (-5) background red parameter is greater than 255<br>
 * (-6) background green parameter is greater than 255<br>
 * (-7) background blue parameter is greater than 255<br>
 * (-8) bold parameter is not a valid BOOL vaiable<br>
 * (-9) dim parameter is not a valid BOOL vaiable<br>
 * (-10) italic parameter is not a valid BOOL vaiable<br>
 * (-11) underline parameter is not a valid BOOL vaiable<br>
 * (-12) blinking parameter is not a valid BOOL vaiable<br>
 * (-13) strikethrough parameter is not a valid BOOL vaiable<br>
 * (-14) doubleunderline parameter is not a valid BOOL vaiable
 */
int setcharformattedunicode(struct UnicodeScreen *unicode, wchar_t *c,
	  unsigned int foregroundRed, unsigned int foregroundGreen, unsigned int foregroundBlue,
      unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
      BOOL bold, BOOL dim, BOOL italic, BOOL underline, BOOL blinking, BOOL strikethrough, BOOL doubleunderline);

/**
 * Sets char on given cursor position. Changes cursor position. Allows to customize character.
 *
 * @param unicode pointer to structure console
 * @param row row number
 * @param col column number
 * @param c char to set
 * @param foregroundRed foreground color red value
 * @param foregroundGreen foreground color green value
 * @param foregroundBlue foreground color blue value
 * @param backgroundRed backround color red value
 * @param backgroundGreen backround color green value
 * @param backgroundBlue backround color blue value
 * @param bold is text bold
 * @param dim is text dim
 * @param italic is text italic
 * @param underline is text underline
 * @param blinking is text blinking
 * @param strikethrough is text strikethrough
 * @param doubleunderline is text doubleunderline
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) console parameter is NULL
 * (-2) row is greater than console height
 * (-3) col is greater than console width
 * (-4) foreground red parameter is greater than 255<br>
 * (-5) foreground green parameter is greater than 255<br>
 * (-6) foreground blue parameter is greater than 255<br>
 * (-7) background red parameter is greater than 255<br>
 * (-8) background green parameter is greater than 255<br>
 * (-9) background blue parameter is greater than 255<br>
 * (-10) bold parameter is not a valid BOOL vaiable<br>
 * (-11) dim parameter is not a valid BOOL vaiable<br>
 * (-12) italic parameter is not a valid BOOL vaiable<br>
 * (-13) underline parameter is not a valid BOOL vaiable<br>
 * (-14) blinking parameter is not a valid BOOL vaiable<br>
 * (-15) strikethrough parameter is not a valid BOOL vaiable<br>
 * (-16) doubleunderline parameter is not a valid BOOL vaiable
 */
int setcharformattedcursorunicode(struct UnicodeScreen *unicode, unsigned int row, unsigned int col, wchar_t *c,
	  unsigned int foregroundRed, unsigned int foregroundGreen, unsigned int foregroundBlue,
      unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
      BOOL bold, BOOL dim, BOOL italic, BOOL underline, BOOL blinking, BOOL strikethrough, BOOL doubleunderline);

/**
 * Sets char on specified position. Do not changes cursor position
 *
 * @param unicode pointer to struct Console
 * @param c char to set
 * @param row row number
 * @param col column number
 *
 * @return 0 if everything went well otherwise returns negative:<br>
 * (-1) console parameter is NULL<br>
 * (-2) row is greater than console height
 * (-3) col is greater than console width
 */
int setcharcursorunicode(struct UnicodeScreen *unicode, wchar_t *c, unsigned int row, unsigned int col);

/**
 * Sets char on cursor position. Changes cursor position
 *
 * @param unicode pointer to structure console
 * @param c char to set
 * @return 0 if eveything went well otherwise returns negative:<br>
 * (-1) console parameter is NULL
 */
int setcharunicode(struct UnicodeScreen *unicode, wchar_t *c);


#endif //PCL_PCL_UNICODE_H