/*
 * Constants.re
 *
 * Constants used across Oni2. Some of these may make sense
 * to pull out to configuration values
 */

let minimumFontSize = 6.;
let defaultFontSize = 14.;

let fontAwesomeRegularPath = "FontAwesome5FreeRegular.otf";
let fontAwesomeSolidPath = "FontAwesome5FreeSolid.otf";

/* Horizontal padding on each side of the minimap */
let minimapPadding = 0;

/*
 * Width of characters in minimap, in pixels
 */
let minimapCharacterWidth = 1;
/*
 * Height of characters in minimap, in pixels
 */
let minimapCharacterHeight = 2;
/*
 * Number of pixels between each line in the minimap
 */
let minimapLineSpacing = 1;
let scrollBarThickness = 15;
let minimapMaxColumn = 120;
let tabHeight = 35;
let notificationWidth = 300;

/*
 * The line count considered a 'large file' - if a file exceeds this limit,
 * some features like syntax highlighting will be disabled.
 * The threshold we set right now is artificially low,
 * because our current textmate highlighting strategy is very slow.
 * We'll switch to a native strategy, and bump this up.
 */
let largeFileLineCountThreshold = 1000;
