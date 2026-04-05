//
// Created by pawel on 03.01.2026.
//

#include "pcl_Unicode.h"

#include <stdio.h>
#include <windows.h>

#include "pcl.h"

struct UnicodeScreen* initunicode(struct Console *console) {
	struct UnicodeScreen *unicode = malloc(sizeof(struct UnicodeScreen));
	if (unicode == NULL) {
		return NULL;
	}

	unicode->cursorVisible = TRUE;
	unicode->cursorstyle = BLINKING_BAR;
	unicode->cursor = 0;

	unicode->decoration.bold = FALSE;
	unicode->decoration.dim = FALSE;
	unicode->decoration.italic = FALSE;
	unicode->decoration.underline = FALSE;
	unicode->decoration.blinking = FALSE;
	unicode->decoration.strikethrough = FALSE;
	unicode->decoration.doubleunderline = FALSE;

	unicode->defaultData1 = ' ';
	unicode->defaultData2 = 0;
	unicode->defaultForegroundRed = 255;
	unicode->defaultForegroundGreen = 255;
	unicode->defaultForegroundBlue = 255;
	unicode->defaultBackgroundRed = 0;
	unicode->defaultBackgroundGreen = 0;
	unicode->defaultBackgroundBlue = 0;

	unicode->foregroundRed = unicode->defaultForegroundRed;
	unicode->foregroundGreen = unicode->defaultForegroundGreen;
	unicode->foregroundBlue = unicode->defaultForegroundBlue;

	unicode->backgroundRed = unicode->defaultBackgroundRed;
	unicode->backgroundGreen = unicode->defaultBackgroundGreen;
	unicode->backgroundBlue = unicode->defaultBackgroundBlue;

	WaitForSingleObject(pclMutexHandle, INFINITE);
	unicode->width = console->width;
	unicode->height = console->height;
	ReleaseMutex(pclMutexHandle);

	/*
	 * unicode->width * unicode->height => characters
	 * (19 + 19 + 1) => colors
	 * (5 * 7) => font
	 * unicode->height => last row
	 * 4 => clear
	 */
	unicode->bufferSize = (unicode->width * unicode->height * (19 + 19 + 1) * (5 * 7) + unicode->height + 4) * 2;
	unicode->buffer = malloc(sizeof (struct AsciiCell) * unicode->bufferSize);
	if (unicode->buffer == NULL) {
		free(unicode);
		return NULL;
	}

	for (int i = 0; i < unicode->bufferSize; i++) {
		unicode->buffer[i].data1 = unicode->defaultData1;
		unicode->buffer[i].data2 = unicode->defaultData2;
		unicode->buffer[i].foregroundRed = unicode->defaultForegroundRed;
		unicode->buffer[i].foregroundGreen = unicode->defaultForegroundGreen;
		unicode->buffer[i].foregroundBlue = unicode->defaultForegroundBlue;
		unicode->buffer[i].backgroundRed = unicode->defaultBackgroundRed;
		unicode->buffer[i].backgroundGreen = unicode->defaultBackgroundGreen;
		unicode->buffer[i].backgroundBlue = unicode->defaultBackgroundBlue;

		unicode->buffer[i].decoration.bold = FALSE;
		unicode->buffer[i].decoration.dim = FALSE;
		unicode->buffer[i].decoration.italic = FALSE;
		unicode->buffer[i].decoration.underline = FALSE;
		unicode->buffer[i].decoration.blinking = FALSE;
		unicode->buffer[i].decoration.strikethrough = FALSE;
		unicode->buffer[i].decoration.doubleunderline = FALSE;
	}

	unicode->outputBuffer = malloc(sizeof (char) * unicode->bufferSize);
	if (unicode->outputBuffer == NULL) {
		free(unicode->buffer);
		free(unicode);
		return NULL;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);
	console->unicodeScreens[console->unicodeScreensIndex] = unicode;
	console->unicodeScreensIndex++;

	void* temp = realloc(console->unicodeScreens,sizeof (struct UnicodeScreen*) * console->unicodeScreensIndex + 1);

	if (temp == NULL) {
		ReleaseMutex(pclMutexHandle);
		free(unicode->buffer);
		free(unicode);
		return NULL;
	}
	console->unicodeScreens = temp;
	ReleaseMutex(pclMutexHandle);

	return unicode;
}

int setunicodeecho(struct Console *console, struct UnicodeScreen *unicodeEcho) {
	if (console == NULL) {
		return -1;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);
	console->unicodeEcho = unicodeEcho;
	ReleaseMutex(pclMutexHandle);

	return 0;
}

int unsetunicodeecho(struct Console *console) {
	if (console == NULL) {
		return -1;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);
	console->unicodeEcho = NULL;
	ReleaseMutex(pclMutexHandle);

	return 0;
}

int setcursorstyleunicode(struct UnicodeScreen *unicode, int style) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->cursorstyle = style;
	return 0;
}

int unsetcursorstyleunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->cursorstyle = BLINKING_BAR;
	return 0;
}

int showcursorunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->cursorVisible = TRUE;
	return 0;
}

int hidecursorunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->cursorVisible = FALSE;
	return 0;
}

int setfontboldunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.bold = TRUE;
	return 0;
}

int unsetfontboldunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.bold = FALSE;
	return 0;
}

int getfontboldunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	return unicode->decoration.bold;
}

int setfontdimunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.dim = TRUE;
	return 0;
}

int unsetfontdimunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.dim = FALSE;
	return 0;
}

int getfontdimunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	return unicode->decoration.dim;
}

int setfontitalicunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.italic = TRUE;
	return 0;
}

int unsetfontitalicunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.italic = FALSE;
	return 0;
}

int getfontitalicunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	return unicode->decoration.italic;
}

int setfontunderlineunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.underline = TRUE;
	return 0;
}

int unsetfontunderlineunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.underline = FALSE;
	return 0;
}

int getfontunderlineunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	return unicode->decoration.underline;
}

int setfontblinkingunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.blinking = TRUE;
	return 0;
}

int unsetfontblinkingunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.blinking = FALSE;
	return 0;
}

int getfontblinkingunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	return unicode->decoration.blinking;
}

int setfontstrikethroughunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.strikethrough = TRUE;
	return 0;
}

int unsetfontstrikethroughunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.strikethrough = FALSE;
	return 0;
}

int getfontstrikethroughunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	return unicode->decoration.strikethrough;
}

int setfontdoubleunderlineunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.doubleunderline = TRUE;
	return 0;
}

int unsetfontdoubleunderlineunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->decoration.doubleunderline = FALSE;
	return 0;
}

int getfontdoubleunderlineunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	return unicode->decoration.doubleunderline;
}

int setforegroundcolorunicode(struct UnicodeScreen *unicode, unsigned int red, unsigned int green, unsigned int blue) {
	if (unicode == NULL) {
		return -1;
	}
	if (red > 255) {
		return -2;
	}
	if (green > 255) {
		return -3;
	}
	if (blue > 255) {
		return -4;
	}
	unicode->foregroundRed = red;
	unicode->foregroundGreen = green;
	unicode->foregroundBlue = blue;
	return 0;
}

int setbackgroundcolorunicode(struct UnicodeScreen *unicode, int red, int green, int blue) {
	if (unicode == NULL) {
		return -1;
	}
	if (red > 255) {
		return -2;
	}
	if (green > 255) {
		return -3;
	}
	if (blue > 255) {
		return -4;
	}
	unicode->backgroundRed = red;
	unicode->backgroundGreen = green;
	unicode->backgroundBlue = blue;
	return 0;
}

int clearforegroundcolorunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->foregroundRed = unicode->defaultForegroundRed;
	unicode->foregroundGreen = unicode->defaultForegroundGreen;
	unicode->foregroundBlue = unicode->defaultForegroundBlue;
	return 0;
}

int clearbackgroundcolorunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}
	unicode->backgroundRed = unicode->defaultBackgroundRed;
	unicode->backgroundGreen = unicode->defaultBackgroundGreen;
	unicode->backgroundBlue = unicode->defaultBackgroundBlue;
	return 0;
}

/*
 * Sets char on cursor position. Changes cursor position.
 * Dangerous! Do not waits for mutex. Partially validates data.
 * Pass only strings of size 1 character
*/
void setcharunicodenotsafe(struct UnicodeScreen *unicode, wchar_t * c, unsigned int foregroundRed, unsigned int foregroundGreen, unsigned int foregroundBlue,
						unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
						struct Decoration decoration) {

	wchar_t data1 = 0, data2 = 0;
	size_t size = wcslen(c);
	if (size == 0) {
		return;
	}
	if (size == 1) {
		data1 = c[0];
	}
	else {
		data1 = c[0];
		data2 = c[1];
	}

	switch (c[0]) {
		case '\n': {
			unicode->cursor += unicode->width;
			unicode->cursor -= unicode->cursor % unicode->width;
			if (unicode->cursor >= unicode->width * unicode->height) {
				unicode->cursor = 0;
			}
			return;
		}
		case '\a': {
			// not supported
			c[0] = unicode->defaultData1;
			c[1] = unicode->defaultData2;
			break;
		}
		case '\b': {
			if (unicode->cursor == 0) {
				return;
			}
			unicode->cursor--;

			unicode->buffer[unicode->cursor].data1 = unicode->defaultData1;
			unicode->buffer[unicode->cursor].data2 = unicode->defaultData2;
			unicode->buffer[unicode->cursor].foregroundRed = unicode->foregroundRed;
			unicode->buffer[unicode->cursor].foregroundGreen = unicode->foregroundGreen;
			unicode->buffer[unicode->cursor].foregroundBlue = unicode->foregroundBlue;
			unicode->buffer[unicode->cursor].backgroundRed = unicode->backgroundRed;
			unicode->buffer[unicode->cursor].backgroundGreen = unicode->backgroundGreen;
			unicode->buffer[unicode->cursor].backgroundBlue = unicode->backgroundBlue;
			return;
		}
		case '\v': {
			unicode->cursor += unicode->width;
			if (unicode->cursor >= unicode->width * unicode->height) {
				unicode->cursor = 0;
			}
			return;
		}
		case '\r': {
			unicode->cursor -= unicode->cursor % unicode->width;
			return;
		}
		case '\f': {
			unicode->cursor = 0;
			return;
		}
		default: break;
	}

	// \n - new line
	// \a - not supported
	// \b - backspace
	// \v - vertical enter
	// \r - carrige return
	// \f - set cursor 0 0
	// \t - tab

	unicode->buffer[unicode->cursor].data1 = data1;
	unicode->buffer[unicode->cursor].data2 = data2;
	unicode->buffer[unicode->cursor].foregroundRed = foregroundRed;
	unicode->buffer[unicode->cursor].foregroundGreen = foregroundGreen;
	unicode->buffer[unicode->cursor].foregroundBlue = foregroundBlue;
	unicode->buffer[unicode->cursor].backgroundRed = backgroundRed;
	unicode->buffer[unicode->cursor].backgroundGreen = backgroundGreen;
	unicode->buffer[unicode->cursor].backgroundBlue = backgroundBlue;

	unicode->buffer[unicode->cursor].decoration = decoration;
	if (unicode->cursor < unicode->width * unicode->height - 1) {
		unicode->cursor++;
	}
}

/*
 * Sets char on specified cursor position.Do not changes cursor position.
 * Dangerous! Do not waits for mutex. Partially validates data.
*/
int setcharcursorunicodenotsafe(struct UnicodeScreen *unicode, wchar_t* c, unsigned int row, unsigned int col,
								unsigned int foregroundRed, unsigned int foregroundGreen, unsigned int foregroundBlue,
								unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
								struct Decoration decoration) {
	unsigned int cursorpos = unicode->cursor;
	unicode->cursor = col + row * unicode->width;

	setcharunicodenotsafe(unicode, c,
						foregroundRed, foregroundGreen, foregroundBlue,
						backgroundRed, backgroundGreen, backgroundBlue,
						decoration);

	unicode->cursor = cursorpos;
	return 0;
}

int setcharunicode(struct UnicodeScreen *unicode, wchar_t *c) {
	if (unicode == NULL) {
		return -1;
	}

	// todo docs
	if (wstrlen(c) != 1) {
		return -2;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);

	setcharunicodenotsafe(unicode, c,
						unicode->foregroundGreen, unicode->foregroundRed, unicode->foregroundBlue,
						unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
						unicode->decoration);

	ReleaseMutex(pclMutexHandle);
	return 0;
}

size_t wstrlen(const wchar_t *str) {
	if (str == NULL) {
		return 0;
	}

	size_t size = 0;
	while (*str) {
		if (*str >= 0xD800 && *str <= 0xDBFF) {
			if (*(str + 1) >= 0xDC00 && *(str + 1) <= 0xDFFF) {
				str++;
			}
		}
		size++;
		str++;
	}
	return size;
}

int setcharformattedunicode(struct UnicodeScreen *unicode, wchar_t * c, unsigned int foregroundRed, unsigned int foregroundGreen, unsigned int foregroundBlue,
						unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
						BOOL bold, BOOL dim, BOOL italic, BOOL underline, BOOL blinking, BOOL strikethrough, BOOL doubleunderline) {
	if (unicode == NULL) {
		return -1;
	}

	if (foregroundRed > 255) {
		return -2;
	}

	if (foregroundGreen > 255) {
		return -3;
	}

	if (foregroundBlue > 255) {
		return -4;
	}

	if (backgroundRed > 255) {
		return -5;
	}

	if (backgroundGreen > 255) {
		return -6;
	}

	if (backgroundBlue > 255) {
		return -7;
	}

	if (bold != TRUE && bold != FALSE) {
		return -8;
	}

	if (dim != TRUE && dim != FALSE) {
		return -9;
	}

	if (italic != TRUE && italic != FALSE) {
		return -10;
	}

	if (underline != TRUE && underline != FALSE) {
		return -11;
	}

	if (blinking != TRUE && blinking != FALSE) {
		return -12;
	}

	if (strikethrough != TRUE && strikethrough != FALSE) {
		return -13;
	}

	if (doubleunderline != TRUE && doubleunderline != FALSE) {
		return -14;
	}

	struct Decoration decoration = {
		bold,
		dim,
		italic,
		underline,
		blinking,
		strikethrough,
		doubleunderline
	};

	WaitForSingleObject(pclMutexHandle, INFINITE);

	setcharunicodenotsafe(unicode, c,
					foregroundGreen, foregroundRed, foregroundBlue,
					backgroundRed, backgroundGreen, backgroundBlue,
					decoration);

	ReleaseMutex(pclMutexHandle);
	return 0;
}

int setcharformattedcursorunicode(struct UnicodeScreen *unicode, unsigned int row, unsigned int col, wchar_t * c, unsigned int foregroundRed, unsigned int foregroundGreen, unsigned int foregroundBlue,
						unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
						BOOL bold, BOOL dim, BOOL italic, BOOL underline, BOOL blinking, BOOL strikethrough, BOOL doubleunderline) {
	if (unicode == NULL) {
		return -1;
	}

	if (row >= unicode->height) {
		return -2;
	}

	if (col >= unicode->width) {
		return -3;
	}

	if (foregroundRed > 255) {
		return -4;
	}

	if (foregroundGreen > 255) {
		return -5;
	}

	if (foregroundBlue > 255) {
		return -6;
	}

	if (backgroundRed > 255) {
		return -7;
	}

	if (backgroundGreen > 255) {
		return -8;
	}

	if (backgroundBlue > 255) {
		return -9;
	}

	if (bold != TRUE && bold != FALSE) {
		return -10;
	}

	if (dim != TRUE && dim != FALSE) {
		return -11;
	}

	if (italic != TRUE && italic != FALSE) {
		return -12;
	}

	if (underline != TRUE && underline != FALSE) {
		return -13;
	}

	if (blinking != TRUE && blinking != FALSE) {
		return -14;
	}

	if (strikethrough != TRUE && strikethrough != FALSE) {
		return -15;
	}

	if (doubleunderline != TRUE && doubleunderline != FALSE) {
		return -16;
	}

	switch (c[0]) { // bug switch by whole character
		case '\n':
		case '\a':
		case '\b':
		case '\v':
		case '\r':
		case '\f': {
			// all special characters are not supported in that functon variant
			return 0;
		}
		default: break;
	}

	// \n - new line
	// \a - not supported (alert/bell)
	// \b - backspace
	// \v - vertical enter
	// \r - carrige return
	// \f - set cursor 0 0
	// \t - tab

	struct Decoration decoration = {
		bold,
		dim,
		italic,
		underline,
		blinking,
		strikethrough,
		doubleunderline
	};

	WaitForSingleObject(pclMutexHandle, INFINITE);

	setcharcursorunicodenotsafe(unicode, c, row, col,
				foregroundRed, foregroundGreen, foregroundBlue,
				backgroundRed, backgroundGreen, backgroundBlue,
				decoration);

	ReleaseMutex(pclMutexHandle);
	return 0;
}

BOOL validateformatstringforsetstringformattedunicode(wchar_t *format) {
	if (format == NULL) {
		return FALSE;
	}

	const size_t length = wcslen(format);

	BOOL openToken = FALSE;
	for (int i = 0; i < length; ++i) {
		char token = format[i];

		// variable check
		if (token == '%') {
			// take next token
			i++;
			token = format[i];
			openToken = TRUE;
			switch (token) {
				case '%':
				case 's':
				case 'd':
				case 'h':
				case 'c':
				case 'f': {
					// standard one letter tokens
					openToken = FALSE;
					break;
				}
				case 'l': {
					openToken = FALSE; // %l
					if (i + 1 < length) {
						switch (format[i + 1]) {
							case 'l': {
								i++; // %ll
								if (i + 1 < length && format[i + 1] == 'f') {
									i++; // %llf
									break;
								}
								break;
							}
							case 'f': {
								i++; // %lf
								break;
							}
							default: ;
						}
					}
					break;
				}
				case 'u': { // unsigned
					if (i + 1 < length) {
						switch (format[i + 1]) {
							case 'l': {
								openToken = FALSE; // %ul
								i++;
								if (i + 1 < length && format[i + 1] == 'l') {
									i++; // %ull
								}
								break;
							}
							case 'd':
							case 'h': {
								openToken = FALSE;
								i++; // %ud and %uh
								break;
							}
							default: ;
						}
					}
					break;
				}
				case '.': { // floating point with precision
					while (TRUE) {
						if (i + 1 < length && isdigit(format[i + 1])) {
							i++; // precision
						}
						else {
							break;
						}
					}
					if (i + 1 < length) {
						switch (format[i + 1]) {
							case 'f': {
								openToken = FALSE; // %.<int>f
								i++;
								break;
							}
							case 'l': {
								i++; // %.<int>lf
								if (i + 1 < length && format[i + 1] == 'l') {
									openToken = FALSE; // %.<int>llf
									i++;
								}
								break;
							}
							default: break;
						}
					}
					break;
				}
				default: ;
			}
		}
		else if (token == '@') {
			// style check
			i++;
			token = format[i];
			openToken = TRUE;

			// font tokens
			switch (token) {
				case 'b':
				case 'd':
				case 'i':
				case 'l':
				case 's':
				case 'c':
				case '@': {
					// standard one letter tokens
					openToken = FALSE;
					break;
				}
				case 'u': {
					openToken = FALSE;
					if (i + 1 < length && format[i + 1] == 'u') {
						i++;
					}
					break;
				}
				case 'r': {
					if (i + 1 < length) {
						i++;
						switch (format[i]) {
							case 'b':
							case 'd':
							case 'i':
							case 'l':
							case 's':{
								// standard one letter tokens remover
								openToken = FALSE;
								break;
							}
							case 'u': {
								openToken = FALSE;
								if (i + 1 < length && format[i + 1] == 'u') {
									i++;
								}
								break;
							}
						}
					}
				}
				default: break;
			}

			// color tokens
			int semicolons = 0;
			while (TRUE) {
				if (i + 1 < length) {
					i++;
					if (format[i] == ';') {
						semicolons++;
						continue;
					}
					if (!isdigit(format[i])) {
						break;
					}
				}
				else {
					break;
				}
			}

			if (semicolons == 2) {
				if (format[i] == 'f' || format[i] == 'b') {
					openToken = FALSE;
					i++;
				}
				else {
					return FALSE;
				}
			}
			else {
				return FALSE;
			}
		}
		// all other tokens are good
	}
	if (openToken) {
		// format string suddenly ends with unfinished token
		return FALSE;
	}

	// format string is valid
	return TRUE;
}

int setcharcursorunicode(struct UnicodeScreen *unicode, wchar_t * c, unsigned int row, unsigned int col) {
	if (unicode == NULL) {
		return -1;
	}

	if (row >= unicode->height) {
		return -2;
	}

	if (col >= unicode->width) {
		return -3;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);

	setcharcursorunicodenotsafe(unicode, c, row, col,
		unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
		unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
		unicode->decoration);

	ReleaseMutex(pclMutexHandle);

	return 0;
}

/*
 * Actual printf like logic. Does not provide any data validation
*/
int setstringformattedunicodenotsafe(struct UnicodeScreen *unicode, wchar_t *format, va_list args) {
	// valid tokens sorted by length
	wchar_t* validtokens[] = {
		L"%ull", L"%ll", L"%uh", L"%ud",
		L"%ul", L"%c", L"%h", L"%d", L"%l", L"%s", L"%%"
	};

	int tokenssize = sizeof(validtokens) / sizeof(validtokens[0]);

	int length = 0;

	while (*format) {

		// standard printf behaviour
		if (*format == '%') {
			format++;

			// floating point numbers printing
			wchar_t* precisionstr = malloc(20 * sizeof(char));
			int precisionstrsize = 10;

			if (*format == '.') {
				// precision detected
				// float match

				format++;

				int i = 0;
				while (isdigit(*format)) {
					precisionstr[i] = *format;
					i++;
					if (i == precisionstrsize) {
						precisionstrsize *= 2;
						if (!realloc(precisionstr, precisionstrsize)) {
							// error
							free(precisionstr);
							va_end(args);
							return -4;
						}
					}
					format++;
				}
				precisionstr[i] = '\0';
			}
			else {
				precisionstr[0] = '5';
				precisionstr[1] = '\0';
			}

			// lets handle that float
			// float
			if (wcsncmp(format, L"f", 1) == 0) {
				format++;
				float f = va_arg(args, double);

				wchar_t* formatstr = malloc((precisionstrsize + 4) * sizeof(char));
				memset(formatstr, 0, (precisionstrsize + 4) * sizeof(char));
				formatstr[0] = '%';
				formatstr[1] = '.';
				wcscat(formatstr, precisionstr);
				wcscat(formatstr, L"f\0");

				int size = snwprintf(NULL, 0, formatstr, f);
				wchar_t* memory = malloc(size * sizeof(char));
				snwprintf(memory, size, formatstr, f);
				setstringunicode(unicode, memory);
				free(memory);
				length += size;
				free(formatstr);
			}
			// double
			if (wcsncmp(format, L"lf", 2) == 0) {
				format += 2;
				double lf = va_arg(args, double);

				wchar_t* formatstr = malloc((precisionstrsize + 4) * sizeof(char));
				memset(formatstr, 0, (precisionstrsize + 4) * sizeof(char));
				formatstr[0] = '%';
				formatstr[1] = '.';
				wcscat(formatstr, precisionstr);
				wcscat(formatstr, L"lf\0");

				int size = snwprintf(NULL, 0, formatstr, lf);
				wchar_t* memory = malloc(size * sizeof(char));
				snwprintf(memory, size, formatstr, lf);
				setstringunicode(unicode, memory);
				free(memory);
				length += size;
				free(formatstr);
			}
			// long double
			if (wcsncmp(format, L"llf", 3) == 0) {
				format += 3;
				long double llf = va_arg(args, long double);

				wchar_t* formatstr = malloc((precisionstrsize + 4) * sizeof(char));
				memset(formatstr, 0, (precisionstrsize + 4) * sizeof(char));
				formatstr[0] = '%';
				formatstr[1] = '.';
				wcscat(formatstr, precisionstr);
				wcscat(formatstr, L"Lf\0");

				int size = snwprintf(NULL, 0, formatstr, llf);
				wchar_t* memory = malloc(size * sizeof(char));
				snwprintf(memory, size, formatstr, llf);
				setstringunicode(unicode, memory);
				free(memory);
				length += size;
				free(formatstr);
			}
			free(precisionstr);

			// standard tokens
			for (int i = 0; i < tokenssize; i++) {
				wchar_t* token = validtokens[i] + 1;
				size_t tokensize = wcslen(token);
				if (wcsncmp(format, token, tokensize) == 0) {
					// match
					format += tokensize;
					if (wcscmp(token, L"%") == 0) {
						setcharunicodenotsafe(unicode, L"%",
											unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
											unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
											unicode->decoration);
						length++;
						break;
					}
					if (wcscmp(token, L"s") == 0) {
						wchar_t* s = va_arg(args, wchar_t*);
						setstringunicode(unicode, s);
						length += (int)wcslen(s);
						break;
					}
					if (wcscmp(token, L"l") == 0) {
						long l = va_arg(args, long);
						int len = snprintf(NULL, 0, "%ld", l);
						wchar_t* longstring = malloc((len+1) * sizeof(wchar_t));
						snwprintf(longstring, len+1, L"%ld", l);
						setstringunicode(unicode, longstring);
						length += (int)wcslen(longstring);
						free(longstring);
						break;
					}
					if (wcscmp(token, L"d") == 0) {
						int d = va_arg(args, int);
						int len = snprintf(NULL, 0, "%d", d);
						wchar_t* intstr = malloc((len+1) * sizeof(wchar_t));
						snwprintf(intstr, len+1, L"%d", d);
						setstringunicode(unicode, intstr);
						length += (int)wcslen(intstr);
						free(intstr);
						break;
					}
					if (wcscmp(token, L"h") == 0) {
						short h = va_arg(args, int);
						int len = snprintf(NULL, 0, "%hd", h);
						wchar_t* shortstr = malloc((len+1) * sizeof(wchar_t));
						snwprintf(shortstr, len+1, L"%hd", h);
						setstringunicode(unicode, shortstr);
						length += (int)wcslen(shortstr);
						free(shortstr);
						break;
					}
					if (wcscmp(token, L"c") == 0) {
						const wchar_t c = va_arg(args, int);
						setcharunicodenotsafe(unicode, &c, // bug analyze and fix
											unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
											unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
											unicode->decoration);
						length++;
						break;
					}
					if (wcscmp(token, L"ul") == 0) {
						unsigned long ul = va_arg(args, unsigned long);
						int len = snprintf(NULL, 0, "%lu", ul);
						wchar_t* unsignedlongstr = malloc((len+1) * sizeof(wchar_t));
						snwprintf(unsignedlongstr, len+1, L"%lu", ul);
						setstringunicode(unicode, unsignedlongstr);
						length += (int)wcslen(unsignedlongstr);
						free(unsignedlongstr);
						break;
					}
					if (wcscmp(token, L"ud") == 0) {
						unsigned int ud = va_arg(args, unsigned int);
						int len = snprintf(NULL, 0, "%u", ud);
						wchar_t* unsignedlongstr = malloc((len+1) * sizeof(wchar_t));
						snwprintf(unsignedlongstr, len+1, L"%u", ud);
						setstringunicode(unicode, unsignedlongstr);
						length += (int)wcslen(unsignedlongstr);
						free(unsignedlongstr);
						break;
					}
					if (wcscmp(token, L"uh") == 0) {
						unsigned short uh = va_arg(args, int);
						int len = snprintf(NULL, 0, "%hu", uh);
						wchar_t* unsignedshortstr = malloc((len+1) * sizeof(wchar_t));
						snwprintf(unsignedshortstr, len+1, L"%hu", uh);
						setstringunicode(unicode, unsignedshortstr);
						length += (int)wcslen(unsignedshortstr);
						free(unsignedshortstr);
						break;
					}
					if (wcscmp(token, L"ll") == 0) {
						long long ll = va_arg(args, long long);
						int len = snprintf(NULL, 0, "%lld", ll);
						wchar_t* unsignedlongstr = malloc((len+1) * sizeof(wchar_t));
						snwprintf(unsignedlongstr, len+1, L"%lld", ll);
						setstringunicode(unicode, unsignedlongstr);
						length += (int)wcslen(unsignedlongstr);
						free(unsignedlongstr);
						break;
					}
					if (wcscmp(token, L"ull") == 0) {
						unsigned long long ull = va_arg(args, unsigned long long );
						int len = snprintf(NULL, 0, "%llu", ull);
						wchar_t* unsignedlongstr = malloc((len+1) * sizeof(wchar_t));
						snwprintf(unsignedlongstr, len+1, L"%llu", ull);
						setstringunicode(unicode, unsignedlongstr);
						length += (int)wcslen(unsignedlongstr);
						free(unsignedlongstr);
						break;
					}
				}
			}
			continue;
		}

		// font styles
		/*
		 * %ull unsigned long long
		 * %ll long long
		 * %uh unsigned short
		 * %ud unsigned int
		 * %ul unsigned long
		 * %c char
		 * %h short
		 * %d int
		 * %l long
		 * %s string
		 * %% '%' character
		 *
		 * Possible styles
		 * @<number>;<number>;<number>f foreground color
		 * @<number>;<number>;<number>b background color
		 * @b bold
		 * @rb remove bold
		 *
		 * @d dim
		 * @rd remove dim
		 *
		 * @i italic
		 * @ri remove italic
		 *
		 * @u underline
		 * @ru remove underline
		 *
		 * @l blinking
		 * @rl remove blinking
		 *
		 * @s strikethrough
		 * @rs remove strikethrough
		 *
		 * @uu doubleunderline
		 * @ruu remove doubleunderline
		 *
		 * @c clear all
		 *
		 * @@ at character
		*/
		if (*format == '@') {
			format++;

			if (*format == '@') {
				format++;
				setcharunicodenotsafe(unicode, L"@",
									unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
									unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
									unicode->decoration);
				length++;
			}
			else if (*format == 'c') {
				format++;

				unicode->buffer[unicode->cursor].decoration.bold = FALSE;
				unicode->buffer[unicode->cursor].decoration.dim = FALSE;
				unicode->buffer[unicode->cursor].decoration.italic = FALSE;
				unicode->buffer[unicode->cursor].decoration.underline = FALSE;
				unicode->buffer[unicode->cursor].decoration.blinking = FALSE;
				unicode->buffer[unicode->cursor].decoration.strikethrough = FALSE;
				unicode->buffer[unicode->cursor].decoration.doubleunderline = FALSE;

				unicode->foregroundRed = unicode->defaultForegroundRed;
				unicode->foregroundGreen = unicode->defaultForegroundGreen;
				unicode->foregroundBlue = unicode->defaultForegroundBlue;
			}
			else if (*format == 'b') {
				format++;
				unicode->decoration.bold = TRUE;
			}
			else if (wcsncmp(format, L"rb", 2) == 0) {
				format += 2;
				unicode->decoration.bold = FALSE;
			}
			else if (*format == 'd') {
				format++;
				unicode->decoration.dim = TRUE;
			}
			else if (wcsncmp(format, L"rd", 2) == 0) {
				format += 2;
				unicode->decoration.dim = FALSE;
			}
			else if (*format == 'i') {
				format++;
				unicode->decoration.italic = TRUE;
			}
			else if (wcsncmp(format, L"ri", 2) == 0) {
				format += 2;
				unicode->decoration.italic = FALSE;
			}
			else if (*format == 'u') {
				format++;
				unicode->decoration.underline = TRUE;
			}
			else if (wcsncmp(format, L"ru", 2) == 0) {
				format += 2;
				unicode->decoration.underline = FALSE;
			}
			else if (*format == 'l') {
				format++;
				unicode->decoration.blinking = TRUE;
			}
			else if (wcsncmp(format, L"rl", 2) == 0) {
				format += 2;
				unicode->decoration.blinking = FALSE;
			}
			else if (*format == 's') {
				format++;
				unicode->decoration.strikethrough = TRUE;
			}
			else if (wcsncmp(format, L"rs", 2) == 0) {
				format += 2;
				unicode->decoration.strikethrough = FALSE;
			}
			else if (wcsncmp(format, L"uu", 2) == 0) {
				format += 2;
				unicode->decoration.doubleunderline = TRUE;
			}
			else if (wcsncmp(format, L"ruu", 3) == 0) {
				format += 3;
				unicode->decoration.doubleunderline = FALSE;
			}
			else if (isdigit(*format)) {
				int r, g, b;
				r = g = b = 0;
				r = wcstol(format, &format, 10);
				format++;
				g = wcstol(format, &format, 10);
				format++;
				b = wcstol(format, &format, 10);
				if (*format == 'f') {

					unicode->foregroundRed = r;
					unicode->foregroundGreen = g;
					unicode->foregroundBlue = b;

				}
				else if (*format == 'b') {

					unicode->backgroundRed = r;
					unicode->backgroundGreen = g;
					unicode->backgroundBlue = b;

				}
				format++;
			}

			continue;
		}

		// standard non-controlling character
		setcharunicodenotsafe(unicode, format, // bug pass only one character
							unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
							unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
							unicode->decoration);
		length++;
		format++;
	}

	return length;
}

int setstringformattedunicode(struct UnicodeScreen *unicode, wchar_t *format, ...) {
	if (unicode == NULL) {
		return -1;
	}

	if (format == NULL) {
		return -2;
	}

	if (!validateformatstringforsetstringformattedunicode(format)) {
		return -3;
	}

	va_list args;
	va_start(args, format);
	int length = setstringformattedunicodenotsafe(unicode, format, args);

	if (length < 0) {
		va_end(args);
		return length;
	}

	va_end(args);
	return length;
}

int setstringformattedcursorunicode(struct UnicodeScreen *unicode, int row, int col, wchar_t * format, ...) {
	if (unicode == NULL) {
		return -1;
	}

	if (row < 0) {
		return -2;
	}

	if (col < 0) {
		return -3;
	}

	if (format == NULL) {
		return -4;
	}

	if (row >= unicode->height) {

		return -5;
	}
	if (col >= unicode->width) {

		return -6;
	}

	if (!validateformatstringforsetstringformattedunicode(format)) {
		return -7;
	}

	unsigned int cursor = unicode->cursor;
	unicode->cursor = col + row * unicode->width;

	va_list args;
	va_start(args, format);
	int length = setstringformattedunicodenotsafe(unicode, format, args);

	if (length < 0) {
		va_end(args);
		return length;
	}

	va_end(args);

	unicode->cursor = cursor;

	return length;
}

int setstringcursorunicode(struct UnicodeScreen *unicode, wchar_t *string, int row, int col) {
	if (unicode == NULL) {
		return -1;
	}

	if (row < 0) {
		return -2;
	}

	if (col < 0) {
		return -3;
	}

	if (string == NULL) {
		return -4;
	}

	if (row >= unicode->height) {

		return -5;
	}
	if (col > unicode->width) {

		return -6;
	}

	const unsigned int cursor = unicode->cursor;
	unicode->cursor = col + row * unicode->width;

	setstringunicode(unicode, string);

	unicode->cursor = cursor;

	return 0;
}

int clearunicode(struct UnicodeScreen *unicode) {
	if (unicode == NULL) {
		return -1;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);
	for (int i = 0; i < unicode->height * unicode->width; ++i) {
		unicode->buffer[i].data1 = unicode->defaultData1;
		unicode->buffer[i].data2 = unicode->defaultData2;
		unicode->buffer[i].foregroundRed = unicode->defaultForegroundRed;
		unicode->buffer[i].foregroundGreen = unicode->defaultForegroundGreen;
		unicode->buffer[i].foregroundBlue = unicode->defaultForegroundBlue;
		unicode->buffer[i].backgroundRed = unicode->defaultBackgroundRed;
		unicode->buffer[i].backgroundGreen = unicode->defaultBackgroundGreen;
		unicode->buffer[i].backgroundBlue = unicode->defaultBackgroundBlue;


		unicode->buffer[i].decoration.bold = FALSE;
		unicode->buffer[i].decoration.dim = FALSE;
		unicode->buffer[i].decoration.italic = FALSE;
		unicode->buffer[i].decoration.underline = FALSE;
		unicode->buffer[i].decoration.blinking = FALSE;
		unicode->buffer[i].decoration.strikethrough = FALSE;
		unicode->buffer[i].decoration.doubleunderline = FALSE;
	}
	unicode->cursor = 0;
	ReleaseMutex(pclMutexHandle);

	return 0;
}

int fillunicode(struct UnicodeScreen *unicode, wchar_t * c, unsigned int foregroundRed, unsigned int foregroundGreen,
	unsigned int foregroundBlue, unsigned int backgroundRed, unsigned int backgroundGreen, unsigned int backgroundBlue,
	BOOL bold, BOOL dim, BOOL italic, BOOL underline, BOOL blinking, BOOL strikethrough, BOOL doubleunderline) {
	if (unicode == NULL) {
		return -1;
	}

	if (foregroundRed > 255) {
		return -2;
	}

	if (foregroundGreen > 255) {
		return -3;
	}

	if (foregroundBlue > 255) {
		return -4;
	}

	if (backgroundRed > 255) {
		return -5;
	}

	if (backgroundGreen > 255) {
		return -6;
	}

	if (backgroundBlue > 255) {
		return -7;
	}

	if (bold != TRUE && bold != FALSE) {
		return -8;
	}

	if (dim != TRUE && dim != FALSE) {
		return -9;
	}

	if (italic != TRUE && italic != FALSE) {
		return -10;
	}

	if (underline != TRUE && underline != FALSE) {
		return -11;
	}

	if (blinking != TRUE && blinking != FALSE) {
		return -12;
	}

	if (strikethrough != TRUE && strikethrough != FALSE) {
		return -13;
	}

	if (doubleunderline != TRUE && doubleunderline != FALSE) {
		return -14;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);
	for (int i = 0; i < unicode->height * unicode->width; ++i) {
		unicode->buffer[i].data1 = c[0]; // bug fix like other
		unicode->buffer[i].data2 = c[1];
		unicode->buffer[i].foregroundRed = foregroundRed;
		unicode->buffer[i].foregroundGreen = foregroundGreen;
		unicode->buffer[i].foregroundBlue = foregroundBlue;
		unicode->buffer[i].backgroundRed = backgroundRed;
		unicode->buffer[i].backgroundGreen = backgroundGreen;
		unicode->buffer[i].backgroundBlue = backgroundBlue;

		unicode->buffer[i].decoration.bold = bold;
		unicode->buffer[i].decoration.dim = dim;
		unicode->buffer[i].decoration.italic = italic;
		unicode->buffer[i].decoration.underline = underline;
		unicode->buffer[i].decoration.blinking = blinking;
		unicode->buffer[i].decoration.strikethrough = strikethrough;
		unicode->buffer[i].decoration.doubleunderline = doubleunderline;
	}
	unicode->cursor = 0;
	ReleaseMutex(pclMutexHandle);

	return 0;
}

int fillcharunicode(struct UnicodeScreen *unicode, wchar_t * c) {
	if (unicode == NULL) {
		return -1;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);
	for (int i = 0; i < unicode->height * unicode->width; ++i) {
		unicode->buffer[i].data1 = c[0]; // todo test
		unicode->buffer[i].data2 = c[1];
		unicode->buffer[i].foregroundRed = unicode->foregroundRed;
		unicode->buffer[i].foregroundGreen = unicode->foregroundGreen;
		unicode->buffer[i].foregroundBlue = unicode->foregroundBlue;
		unicode->buffer[i].backgroundRed = unicode->backgroundRed;
		unicode->buffer[i].backgroundGreen = unicode->backgroundGreen;
		unicode->buffer[i].backgroundBlue = unicode->backgroundBlue;

		unicode->buffer[i].decoration = unicode->decoration;
	}
	ReleaseMutex(pclMutexHandle);
	unicode->cursor = 0;

	return 0;
}

int set2darrayunicode(struct UnicodeScreen *unicode, wchar_t* array, unsigned int row, unsigned int col, unsigned int width, unsigned int height) {
	if (unicode == NULL) {
		return -1;
	}

	if (array == NULL) {
		return -2;
	}

	if (height == 0) {
		return -3;
	}

	if (width == 0) {
		return -4;
	}

	/*
	// if we want to show only arrays that can be showed entirely
	if (height + row > unicode->height) {
		return -5;
	}

	if (width + col > unicode->width) {
		return -6;
	}*/

	WaitForSingleObject(pclMutexHandle, INFINITE);
	for (int i = 0; i < height * width; ++i) {
		unsigned int r = row + i / width;
		unsigned int c = col + i % width;
		if (r < unicode->height && c < unicode->width) {
			setcharcursorunicodenotsafe(unicode, array/* bug pass only one character not entire string */, r, c,
				unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
				unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
				unicode->decoration);
		}
	}
	ReleaseMutex(pclMutexHandle);
	return 0;
}

int setcursorpositionunicode(struct UnicodeScreen *unicode, unsigned int row, unsigned int col) {
	if (unicode == NULL) {
		return -1;
	}

	if (row >= unicode->height) {

		return -2;
	}
	if (col >= unicode->width) {

		return -3;
	}

	unicode->cursor = col + row * unicode->width;

	return 0;
}

int getcursorpositionunicode(struct UnicodeScreen *unicode, unsigned int *row, unsigned int *col) {
	if (unicode == NULL) {
		return -1;
	}
	if (row == NULL) {
		return -2;
	}
	if (col == NULL) {
		return -3;
	}
	*row = unicode->cursor / unicode->width;
	*col = unicode->cursor % unicode->width;

	return 0;
}

int refreshunicode(struct Console* console, struct UnicodeScreen* unicode) {
	if (unicode == NULL) {
		return -1;
	}

	// init
	int place = 0;

	// set cursor position to top left
	wchar_t buff[4];
	int add = wsprintfW(buff, L"\x1B[H");

	// init
	WaitForSingleObject(pclMutexHandle, INFINITE);
	memset(unicode->outputBuffer, 0, unicode->bufferSize);
	memcpy(&unicode->outputBuffer[place], buff, add+2);

	place += add;

	unsigned int foregroundRed = 255;
	unsigned int foregroundGreen = 255;
	unsigned int foregroundBlue = 255;
	unsigned int backgroundRed = 0;
	unsigned int backgroundGreen = 0;
	unsigned int backgroundBlue = 0;

	struct Decoration current;
	current.bold = FALSE;
	current.italic = FALSE;
	current.dim = FALSE;
	current.underline = FALSE;
	current.blinking = FALSE;
	current.strikethrough = FALSE;
	current.doubleunderline = FALSE;

	for (int i = 0; i < unicode->height * unicode->width; ++i) {
		if (i != 0 && i % unicode->width == 0) {
			unicode->outputBuffer[place] = '\n';
			place++;
		}

		struct UnicodeCell cell = unicode->buffer[i];

		if (current.bold != cell.decoration.bold) {
			if (cell.decoration.bold == TRUE) {
				current.bold = TRUE;
				char boldstr[4] = "\x1B[1m";
				memcpy(&unicode->outputBuffer[place], boldstr, 4);
				place += 4;
			}
			else {
				current.bold = FALSE;
				char boldstr[5] = "\x1B[22m";
				memcpy(&unicode->outputBuffer[place], boldstr, 5);
				place += 5;
			}
		}

		if (current.dim != cell.decoration.dim) {
			if (cell.decoration.dim == TRUE) {
				current.dim = TRUE;
				char dimstr[4] = "\x1B[2m";
				memcpy(&unicode->outputBuffer[place], dimstr, 4);
				place += 4;
			}
			else {
				current.dim = FALSE;
				char dimstr[5] = "\x1B[22m";
				memcpy(&unicode->outputBuffer[place], dimstr, 5);
				place += 5;
			}
		}

		if (current.italic != cell.decoration.italic) {
			if (cell.decoration.italic == TRUE) {
				current.italic = TRUE;
				char italicstr[4] = "\x1B[3m";
				memcpy(&unicode->outputBuffer[place], italicstr, 4);
				place += 4;
			}
			else {
				current.italic = FALSE;
				char italicstr[5] = "\x1B[23m";
				memcpy(&unicode->outputBuffer[place], italicstr, 5);
				place += 5;
			}
		}

		if (current.underline != cell.decoration.underline) {
			if (cell.decoration.underline == TRUE) {
				current.underline = TRUE;
				char underlinestr[4] = "\x1B[4m";
				memcpy(&unicode->outputBuffer[place], underlinestr, 4);
				place += 4;
			}
			else {
				current.underline = FALSE;
				char underlinestr[5] = "\x1B[24m";
				memcpy(&unicode->outputBuffer[place], underlinestr, 5);
				place += 5;
			}
		}

		if (current.blinking != cell.decoration.blinking) {
			if (cell.decoration.blinking == TRUE) {
				current.blinking = TRUE;
				char blinkingstr[4] = "\x1B[5m";
				memcpy(&unicode->outputBuffer[place], blinkingstr, 4);
				place += 4;
			}
			else {
				current.blinking = FALSE;
				char blinkingstr[5] = "\x1B[25m";
				memcpy(&unicode->outputBuffer[place], blinkingstr, 5);
				place += 5;
			}
		}

		if (current.strikethrough != cell.decoration.strikethrough) {
			if (cell.decoration.strikethrough == TRUE) {
				current.strikethrough = TRUE;
				char strikethroughstr[4] = "\x1B[9m";
				memcpy(&unicode->outputBuffer[place], strikethroughstr, 4);
				place += 4;
			}
			else {
				current.strikethrough = FALSE;
				char strikethroughstr[5] = "\x1B[29m";
				memcpy(&unicode->outputBuffer[place], strikethroughstr, 5);
				place += 5;
			}
		}

		if (current.doubleunderline != cell.decoration.doubleunderline) {
			if (cell.decoration.doubleunderline == TRUE) {
				current.doubleunderline = TRUE;
				char doubleunderlinestr[5] = "\x1B[21m";
				memcpy(&unicode->outputBuffer[place], doubleunderlinestr, 5);
				place += 5;
			}
			else {
				current.doubleunderline = FALSE;
				char doubleunderlinestr[5] = "\x1B[24m";
				memcpy(&unicode->outputBuffer[place], doubleunderlinestr, 5);
				place += 5;
			}
		}

		if (foregroundRed != cell.foregroundRed || foregroundGreen != cell.foregroundGreen || foregroundBlue != cell.foregroundBlue) {
			foregroundRed = cell.foregroundRed;
			foregroundGreen = cell.foregroundGreen;
			foregroundBlue = cell.foregroundBlue;
			wchar_t colorbuff[20];
			add = wsprintfW(colorbuff, L"\x1B[38;2;%d;%d;%dm", foregroundRed, foregroundGreen, foregroundBlue);
			memcpy(&unicode->outputBuffer[place], colorbuff, add);
			place += add;
		}
		if (backgroundRed != cell.backgroundRed || backgroundGreen != cell.backgroundGreen || backgroundBlue != cell.backgroundBlue) {
			backgroundRed = cell.backgroundRed;
			backgroundGreen = cell.backgroundGreen;
			backgroundBlue = cell.backgroundBlue;
			wchar_t colorbuff[20];
			add = wsprintfW(colorbuff, L"\x1B[48;2;%d;%d;%dm", backgroundRed, backgroundGreen, backgroundBlue);
			memcpy(&unicode->outputBuffer[place], colorbuff, add);
			place += add;
		}


		unicode->outputBuffer[place] = cell.data1;
		place++;
		if (cell.data2 != 0) {
			unicode->outputBuffer[place] = cell.data2;
			place++;
		}
	}

	unicode->outputBuffer[place] = '\0';
	WriteConsoleW(console->outputHandle, unicode->outputBuffer, wcslen(unicode->outputBuffer), NULL, NULL);

	// setting curosor position
	unsigned int row = unicode->cursor / unicode->width + 1;
	unsigned int col = unicode->cursor % unicode->width + 1;
	wchar_t position[30];
	wsprintfW(position, L"\x1B[%d;%dH", row, col);
	WriteConsoleW(console->outputHandle, position, wcslen(position), NULL, NULL);

	wchar_t* cursorstyle;
	switch (unicode->cursorstyle) {
		case BLINKING_BLOCK: {
			cursorstyle = L"\x1B[1 q";
			break;
		}
		case STEADY_BLOCK: {
			cursorstyle = L"\x1B[2 q";
			break;
		}
		case BLINKING_UNDERLINE: {
			cursorstyle = L"\x1B[3 q";
			break;
		}
		case STEADY_UNDERLINE: {
			cursorstyle = L"\x1B[4 q";
			break;
		}
		default:
		case BLINKING_BAR: {
			cursorstyle = L"\x1B[5 q";
			break;
		}
		case STEADY_BAR: {
			cursorstyle = L"\x1B[6 q";
			break;
		}
	}

	WriteConsoleW(console->outputHandle, cursorstyle, wcslen(cursorstyle), NULL, NULL);

	if (unicode->cursorVisible) {
		wchar_t* show = L"\x1B[?25h";
		WriteConsoleW(console->outputHandle, show, wcslen(show), NULL, NULL);
	}
	else {
		wchar_t* hide = L"\x1B[?25l";
		WriteConsoleW(console->outputHandle, hide, wcslen(hide), NULL, NULL);
	}

	ReleaseMutex(pclMutexHandle);

	return 0;
}

int setstringunicode(struct UnicodeScreen *unicode, wchar_t *string) {
	if (unicode == NULL) {
		return -1;
	}
	if (string == NULL) {
		return -2;
	}
	const size_t size = wcslen(string);
	WaitForSingleObject(pclMutexHandle, INFINITE);
	for (int i = 0; i < size; ++i) {
		if (i + 1 < size &&	0xD800 <= string[i] && string[i] <= 0xDBFF && 0xDC00 <= string[i + 1] && string[i + 1] <= 0xDFFF) {
			wchar_t pair[3] = { string[i], string[i + 1], L'\0' };

			setcharunicodenotsafe(unicode, pair,
				unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
				unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
				unicode->decoration);

			i++;
		} else {
			wchar_t single[2] = { string[i], L'\0' };

			setcharunicodenotsafe(unicode, single,
				unicode->foregroundRed, unicode->foregroundGreen, unicode->foregroundBlue,
				unicode->backgroundRed, unicode->backgroundGreen, unicode->backgroundBlue,
				unicode->decoration);
		}

	}
	ReleaseMutex(pclMutexHandle);
	return 0;
}

int getdimensionsunicode(struct UnicodeScreen *unicode, unsigned int* width, unsigned int* height) {
	if (width == NULL) {
		return -1;
	}
	if (height == NULL) {
		return -2;
	}
	if (unicode == NULL) {
		*width = 0;
		*height = 0;
		return -3;
	}

	WaitForSingleObject(pclMutexHandle, INFINITE);
	*width = unicode->width;
	*height = unicode->height;
	ReleaseMutex(pclMutexHandle);

	return 0;
}
