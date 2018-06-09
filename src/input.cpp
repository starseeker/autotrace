/* input.c: interface for input handlers

   Copyright (C) 1999, 2000, 2001 Bernhard Herzog.
   Copyright (C) 2003 Masatake YAMATO

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */

#include "autotrace.h"
#include "private.h"
#include "input.h"
#include "xstd.h"
#include "filename.h"
#include "glibReplacement.h"
#include <string>
#include <map>
#include <algorithm>
#include <cstring>


struct at_input_format_entry {
  at_input_format_entry(std::string description, at_input_func inputFunc) : description(std::move(description)) {
    reader.func = inputFunc;
  }

  at_bitmap_reader reader{};
  const std::string description;
};

static std::map<const std::string, at_input_format_entry> inputFormatMap;
/*
 * Helper functions
 */

int at_input_add_handler(const char *suffix, const char *description, at_input_func writer) {
  return at_input_add_handler_full(suffix, description, writer);
}

int at_input_add_handler_full(const char *suffix, const char *description, at_input_func reader)
{
  g_return_val_if_fail(suffix, 0);
  g_return_val_if_fail(description, 0);
  g_return_val_if_fail(reader, 0);

  std::string suffixString{suffix};
  std::transform(suffixString.begin(), suffixString.end(), suffixString.begin(), ::tolower);

  inputFormatMap.insert({suffixString, at_input_format_entry(description, reader)});

  return 1;
}

at_bitmap_reader *at_input_get_handler(char *filename) {
  char *dot_pos = strrchr(filename, '.');
  dot_pos++;
  if (dot_pos == nullptr)
    dot_pos = const_cast<char *>("");

  return at_input_get_handler_by_suffix(dot_pos);
}

at_bitmap_reader *at_input_get_handler_by_suffix(char *suffix)
{
  if (!suffix || suffix[0] == '\0')
    return nullptr;

  std::string suffixString{suffix};

  std::transform(suffixString.begin(), suffixString.end(), suffixString.begin(), ::tolower);

  auto format = inputFormatMap.find(suffixString);

  if (format != inputFormatMap.end())
    return &(format->second.reader);
  else
    return nullptr;
}

void printInputFormatInfo(FILE *file) {
  for (const auto &inputFormat : inputFormatMap) {
    fprintf(file, "%10s %s\n", inputFormat.first.c_str(), inputFormat.second.description.c_str());
  }
}
