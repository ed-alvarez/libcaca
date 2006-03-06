/*
 *  libcucul      Unicode canvas library
 *  Copyright (c) 2002-2006 Sam Hocevar <sam@zoy.org>
 *                All Rights Reserved
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the Do What The Fuck You Want To
 *  Public License, Version 2, as published by Sam Hocevar. See
 *  http://sam.zoy.org/wtfpl/COPYING for more details.
 */

/** \file box.c
 *  \version \$Id$
 *  \author Sam Hocevar <sam@zoy.org>
 *  \brief Simple box drawing
 *
 *  This file contains box drawing functions, both filled and outline.
 */

#include "config.h"

#if defined(HAVE_INTTYPES_H) || defined(_DOXYGEN_SKIP_ME)
#   include <inttypes.h>
#else
typedef unsigned char uint8_t;
#endif

#include <stdlib.h>

#include "cucul.h"
#include "cucul_internals.h"

/**
 * \brief Draw a box on the screen using the given character.
 *
 * \param x1 X coordinate of the upper-left corner of the box.
 * \param y1 Y coordinate of the upper-left corner of the box.
 * \param x2 X coordinate of the lower-right corner of the box.
 * \param y2 Y coordinate of the lower-right corner of the box.
 * \param c Character to draw the box outline with.
 * \return void
 */
void cucul_draw_box(cucul_t *qq, int x1, int y1, int x2, int y2, char c)
{
    cucul_draw_line(qq, x1, y1, x1, y2, c);
    cucul_draw_line(qq, x1, y2, x2, y2, c);
    cucul_draw_line(qq, x2, y2, x2, y1, c);
    cucul_draw_line(qq, x2, y1, x1, y1, c);
}

/**
 * \brief Draw a thin box on the screen.
 *
 * \param x1 X coordinate of the upper-left corner of the box.
 * \param y1 Y coordinate of the upper-left corner of the box.
 * \param x2 X coordinate of the lower-right corner of the box.
 * \param y2 Y coordinate of the lower-right corner of the box.
 * \return void
 */
void cucul_draw_thin_box(cucul_t *qq, int x1, int y1, int x2, int y2)
{
    int x, y, xmax, ymax;

    if(x1 > x2)
    {
        int tmp = x1;
        x1 = x2; x2 = tmp;
    }

    if(y1 > y2)
    {
        int tmp = y1;
        y1 = y2; y2 = tmp;
    }

    xmax = qq->width - 1;
    ymax = qq->height - 1;

    if(x2 < 0 || y2 < 0 || x1 > xmax || y1 > ymax)
        return;

    /* Draw edges */
    if(y1 >= 0)
        for(x = x1 < 0 ? 1 : x1 + 1; x < x2 && x < xmax; x++)
            cucul_putchar(qq, x, y1, '-');

    if(y2 <= ymax)
        for(x = x1 < 0 ? 1 : x1 + 1; x < x2 && x < xmax; x++)
            cucul_putchar(qq, x, y2, '-');

    if(x1 >= 0)
        for(y = y1 < 0 ? 1 : y1 + 1; y < y2 && y < ymax; y++)
            cucul_putchar(qq, x1, y, '|');

    if(x2 <= xmax)
        for(y = y1 < 0 ? 1 : y1 + 1; y < y2 && y < ymax; y++)
            cucul_putchar(qq, x2, y, '|');

    /* Draw corners */
    if(x1 >= 0 && y1 >= 0)
        cucul_putchar(qq, x1, y1, ',');

    if(x1 >= 0 && y2 <= ymax)
        cucul_putchar(qq, x1, y2, '`');

    if(x2 <= xmax && y1 >= 0)
        cucul_putchar(qq, x2, y1, '.');

    if(x2 <= xmax && y2 <= ymax)
        cucul_putchar(qq, x2, y2, '\'');
}

/**
 * \brief Fill a box on the screen using the given character.
 *
 * \param x1 X coordinate of the upper-left corner of the box.
 * \param y1 Y coordinate of the upper-left corner of the box.
 * \param x2 X coordinate of the lower-right corner of the box.
 * \param y2 Y coordinate of the lower-right corner of the box.
 * \param c Character to fill the box with.
 * \return void
 */
void cucul_fill_box(cucul_t *qq, int x1, int y1, int x2, int y2, char c)
{
    int x, y, xmax, ymax;

    if(x1 > x2)
    {
        int tmp = x1;
        x1 = x2; x2 = tmp;
    }

    if(y1 > y2)
    {
        int tmp = y1;
        y1 = y2; y2 = tmp;
    }

    xmax = qq->width - 1;
    ymax = qq->height - 1;

    if(x2 < 0 || y2 < 0 || x1 > xmax || y1 > ymax)
        return;

    if(x1 < 0) x1 = 0;
    if(y1 < 0) y1 = 0;
    if(x2 > xmax) x2 = xmax;
    if(y2 > ymax) y2 = ymax;

    for(y = y1; y <= y2; y++)
        for(x = x1; x <= x2; x++)
            cucul_putchar(qq, x, y, c);
}

