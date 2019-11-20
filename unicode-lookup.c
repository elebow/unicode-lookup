/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2016 Eddie Lebow
 */

//gcc -O2 unicode-lookup.c -o unicode-lookup -l uninameslist

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uninameslist.h>
#include <wchar.h>

void print_info(const wchar_t ch) {
	const char *name = uniNamesList_name(ch);
	const char *annot = uniNamesList_annot(ch);

	printf("%lc\tU+%x\t(%d dec)\t%s\n", ch, ch, ch, name);
	if (annot) {
		printf("%s\n", annot);
	}
}

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s [input string]\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (!setlocale(LC_CTYPE, "")) {
		fputs("Can't set the specified locale. Check LANG, LC_CTYPE, LC_ALL.\n", stderr);
		return EXIT_FAILURE;
	}

	size_t count = 0;
	while (1) {
		wchar_t ch;
		size_t inc_bytes = mbtowc(&ch, argv[1]+count, MB_CUR_MAX);
		count += inc_bytes;

		if (inc_bytes == 0)
			break;

		print_info(ch);
	}

	return EXIT_SUCCESS;
}
