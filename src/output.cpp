/* output.c: interface for output handlers

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

/* TODO: Unify output codes and input codes. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */

#include "autotrace.h"
#include "private.h"
#include "output.h"
#include "xstd.h"
#include "filename.h"
#include "glibReplacement.h"
#include <cstring>
#include <string>
#include <locale>
#include <algorithm>
#include <map>
#include <utility>

struct at_output_format_entry {
  at_output_format_entry(std::string description, at_output_func outputFunc) : description(std::move(description)) {
    writer.func = outputFunc;
  }

  at_spline_writer writer{};
  const std::string description;
};

static std::map<const std::string, at_output_format_entry> outputFormatMap;
/*
 * Helper functions
 */

int at_output_add_handler(const char *suffix, const char *description, at_output_func writer) {
  g_return_val_if_fail(suffix, 0);
  g_return_val_if_fail(description, 0);
  g_return_val_if_fail(writer, 0);

  std::string suffixString{suffix};
  std::transform(suffixString.begin(), suffixString.end(), suffixString.begin(), ::tolower);

  outputFormatMap.insert({suffixString, {description, writer}});

  return 1;
}

at_spline_writer *at_output_get_handler(char *filename) {
  char *dot_pos = strrchr(filename, '.');
  dot_pos++;
  if (dot_pos == nullptr)
    dot_pos = const_cast<char *>("");

  return at_output_get_handler_by_suffix(dot_pos);
}

at_spline_writer *at_output_get_handler_by_suffix(char *suffix)
{
  if (!suffix || suffix[0] == '\0')
    return nullptr;

  std::string suffixString{suffix};

  std::transform(suffixString.begin(), suffixString.end(), suffixString.begin(), ::tolower);

  const auto format = outputFormatMap.find(suffixString);

  if (format != outputFormatMap.end())
    return &(format->second.writer);
  else
    return nullptr;
}

void printOutputFormatInfo(FILE *file) {
  for (const auto &outputFormat : outputFormatMap) {
    fprintf(file, "%10s %s\n", outputFormat.first.c_str(), outputFormat.second.description.c_str());
  }
}
