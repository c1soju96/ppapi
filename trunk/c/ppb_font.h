// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_C_PPB_FONT_H_
#define PPAPI_C_PPB_FONT_H_

#include "ppapi/c/pp_module.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

#define PPB_FONT_INTERFACE "PPB_Font;1"

typedef struct _pp_Point PP_Point;
typedef struct _pp_Rect PP_Rect;

typedef enum _pp_FontFamily {
  // Uses the user's default web page font (normally either the default serif
  // or sans serif font).
  PP_FONTFAMILY_DEFAULT = 0,

  // These families will use the default web page font corresponding to the
  // given family.
  PP_FONTFAMILY_SERIF = 1,
  PP_FONTFAMILY_SANSSERIF = 2,
  PP_FONTFAMILY_MONOSPACE = 3
} PP_FontFamily;

typedef enum _pp_FontWeight {
  PP_FONTWEIGHT_100 = 0,
  PP_FONTWEIGHT_200,
  PP_FONTWEIGHT_300,
  PP_FONTWEIGHT_400,
  PP_FONTWEIGHT_500,
  PP_FONTWEIGHT_600,
  PP_FONTWEIGHT_700,
  PP_FONTWEIGHT_800,
  PP_FONTWEIGHT_900,
  PP_FONTWEIGHT_NORMAL = PP_FONTWEIGHT_400,
  PP_FONTWEIGHT_BOLD = PP_FONTWEIGHT_700
} PP_FontWeight;

typedef struct _pp_FontDescription {
  // Font face name as a string. This can also be a Null var, in which case the
  // generic family will be obeyed.
  PP_Var face;

  // When face is a Null string, this specifies the generic font family type
  // to use. If the face is specified, this will be ignored.
  PP_FontFamily family;

  uint32_t size;

  // Normally you will use either PP_FONTWEIGHT_NORMAL or PP_FONTWEIGHT_BOLD.
  PP_FontWeight weight;

  bool italic;
  bool small_caps;

  // Adjustment to apply to letter and word spacing, respectively. Initialize
  // to 0 to get normal spacing. Negative values bring letters/words closer
  // together, positive values separate them.
  int letter_spacing;
  int word_spacing;
} PP_FontDescription;

typedef struct _pp_FontMetrics {
  int32_t height;
  int32_t ascent;
  int32_t descent;
  int32_t line_spacing;
  int32_t x_height;
  int32_t average_char_width;
} PP_FontMetrics;

typedef struct _pp_TextRun {
  // This var must either be a string or a null var (which will be treated as
  // a 0-length string).
  PP_Var text;

  // Set to true if the text is right-to-left.
  bool rtl;

  // Set to true to force the directionality of the text regardless of content
  bool override_direction;
} PP_TextRun;

typedef struct _ppb_Font {
  // Returns a font which best matches the given description. The return value
  // will have a non-zero ID on success, or zero on failure.
  PP_Resource (*Create)(PP_Module module,
                        const PP_FontDescription* description);

  // Returns true if the given resource is a Font. Returns false if the
  // resource is invalid or some type other than a Font.
  bool (*IsFont)(PP_Resource resource);

  // Loads the description and metrics of the font into the given structures.
  // The description will be different than the description the font was
  // created with since it will be filled with the real values from the font
  // that was actually selected.
  //
  // The PP_Var in the description should be of type Void on input. On output,
  // this will contain the string and will have a reference count of 1. The
  // plugin is responsible for calling Release on this var.
  //
  // Returns true on success, false if the font is invalid or if the Var in
  // the description isn't Null (to prevent leaks).
  bool (*Describe)(PP_Resource font,
                   PP_FontDescription* description,
                   PP_FontMetrics* metrics);

  // Draws the text to the image buffer.
  //
  // The given point represents the baseline of the left edge of the font,
  // regardless of whether it is left-to-right or right-to-left (in the case of
  // RTL text, this will actually represent the logical end of the text).
  //
  // The clip is optional and may be NULL. In this case, the text will be
  // clipped to the image.
  //
  // The image_data_is_opaque flag indicates whether subpixel antialiasing can
  // be performend, if it is supported. When the image below the text is
  // opaque, subpixel antialiasing is supported and you should set this to true
  // to pick up the user's default preferences. If your plugin is partially
  // transparent, then subpixel antialiasing is not possible and grayscale
  // antialiasing will be used instead (assuming the user has antialiasing
  // enabled at all).
  bool (*DrawTextAt)(PP_Resource font,
                     PP_Resource image_data,
                     const PP_TextRun* text,
                     const PP_Point* position,
                     uint32_t color,
                     const PP_Rect* clip,
                     bool image_data_is_opaque);

  // Returns the width of the given string. If the font is invalid or the var
  // isn't a valid string, this will return -1.
  //
  // Note that this function handles complex scripts such as Arabic, combining
  // accents, etc. so that adding the width of substrings won't necessarily
  // produce the correct width of the entire string.
  int32_t (*MeasureText)(PP_Resource font,
                         const PP_TextRun* text);

  // Returns the character at the given pixel X position from the beginning of
  // the string. This handles complex scripts such as Arabic, where characters
  // may be combined or replaced depending on the context.
  uint32_t (*CharacterOffsetForPixel)(PP_Resource font,
                                      const PP_TextRun* text,
                                      int32_t pixel_position);

  // Returns the horizontal advance to the given character if the string was
  // placed at the given position. This handles complex scripts such as Arabic,
  // where characters may be combined or replaced depending on context.
  int32_t (*PixelOffsetForCharacter)(PP_Resource font,
                                     const PP_TextRun* text,
                                     uint32_t char_offset);
} PPB_Font;

#endif  // PPAPI_C_PPB_FONT_H_
