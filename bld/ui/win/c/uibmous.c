/****************************************************************************
*
*                            Open Watcom Project
*
* Copyright (c) 2002-2018 The Open Watcom Contributors. All Rights Reserved.
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "uidef.h"
#include "uimouse.h"


#define OFF_SCREEN      200

static MOUSEORD OldMouseRow;
static MOUSEORD OldMouseCol = OFF_SCREEN;
static bool     mouseOn = false;
static ATTR     OldAttr;

static LP_STRING RegenPos( unsigned row, unsigned col )
/*****************************************************/
{
    LP_STRING   pos;

    pos = (LP_STRING)UIData->screen.origin
          + ( row * UIData->screen.increment + col ) * sizeof( PIXEL ) + 1;
    return( pos );
}

static void uisetmouseoff( void )
/*******************************/
{
    LP_STRING   old;

    if( mouseOn ) {
        old = RegenPos( OldMouseRow, OldMouseCol );
        *old = OldAttr;
//      physupdate( NULL );
    }
}

static void uisetmouseon( MOUSEORD row, MOUSEORD col )
/****************************************************/
{
    LP_STRING   new;

    if( mouseOn ) {
        new = RegenPos( row, col );
        OldAttr = *new;
        if( UIData->colour == M_MONO ) {
            *new = (OldAttr & 0x79) ^ 0x71;
        } else {
            *new = (OldAttr & 0x7f) ^ 0x77;
        }
//      physupdate( NULL );
        OldMouseRow = row;
        OldMouseCol = col;
    }
}



void UIAPI uisetmouse( MOUSEORD row, MOUSEORD col )
/**************************************************/
{
    if( OldMouseRow == row && OldMouseCol == col )
        return;
    uisetmouseoff();
    uisetmouseon( row, col );
}


void UIAPI uimouse( mouse_func func )
/***********************************/
{
    if( func == MOUSE_ON ) {
        mouseOn = true;
        uisetmouseon( OldMouseRow, OldMouseCol );
    } else {
        uisetmouseoff();
        mouseOn = false;
    }
}
