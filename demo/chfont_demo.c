/*
 * << Haru Free PDF Library 2.0.0 >> -- chfont_demo.c
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#include <stdio.h>

#ifdef LIBHPDF_ASIAN_SUPPORT

#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "grid_sheet.h"
#include "handler.h"
#include "utils.h"

int
main (int argc, char **argv)
{
    HPDF_Doc  pdf;
    HPDF_Page page;
    char fname[256];
    char buf[1024];
    FILE *cp932;
    FILE *cp936;
    const char *fcp936_name;
    const char *fcp932_name;
    HPDF_Font fcp936;
    HPDF_Font fcp932;

    if (argc < 4) {
        printf ("chfont_demo <cp936-ttc-font-file-name> "
                "<cp936-index> <cp932-ttc-font-file-name> <cp932-index>\n");
        return 1;
    }

    strcpy (fname, "mbtext");
    strcat (fname, FILE_SEPARATOR);
    strcat (fname, "cp932.txt");
    cp932 = fopen (fname, "rb");
    if (!cp932) {
        printf ("error: cannot open cp932.txt\n");
        return 1;
    }

    strcpy (fname, "mbtext");
    strcat (fname, FILE_SEPARATOR);
    strcat (fname, "cp936.txt");
    cp936 = fopen (fname, "rb");
    if (!cp936) {
        printf ("error: cannot open cp936.txt\n");
        return 1;
    }

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    pdf = HPDF_New (demo_error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);
    HPDF_UseJPEncodings (pdf);
    HPDF_UseCNSEncodings (pdf);

    fcp936_name = HPDF_LoadTTFontFromFile2 (pdf, argv[1], atoi(argv[2]),
            HPDF_TRUE);
    fcp932_name = HPDF_LoadTTFontFromFile2 (pdf, argv[3], atoi(argv[4]),
            HPDF_TRUE);

    /* add a new page object. */
    page = HPDF_AddPage (pdf);

    HPDF_Page_SetHeight (page, 300);
    HPDF_Page_SetWidth (page, 550);

    fcp936 = HPDF_GetFont (pdf, fcp936_name, "GBK-EUC-H");
    fcp932 = HPDF_GetFont (pdf, fcp932_name, "90ms-RKSJ-H");

    print_grid  (pdf, page);

    HPDF_Page_SetTextLeading (page, 20);

    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, 50, 250);
    HPDF_Page_SetTextLeading (page, 25);

    while (fgets (buf, 1024, cp936)) {
        HPDF_Page_SetFontAndSize (page, fcp936, 18);
        buf [strlen (buf)] = 0;
        HPDF_Page_ShowText (page, buf);

        if (fgets (buf, 1024, cp932)) {
            HPDF_Page_SetFontAndSize (page, fcp932, 18);
            buf [strlen (buf)] = 0;
            HPDF_Page_ShowText (page, buf);
        }

        HPDF_Page_MoveToNextLine (page);
    }

    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    fclose (cp936);
    fclose (cp932);

    return 0;
}

#else /* LIBHPDF_ASIAN_SUPPORT */

int main()
{
    printf("WARNING: chfont_demo was not built correctly. \n"
           "Make sure Asian support is enabled, see LIBHPDF_ASIAN_SUPPORT.\n");
    return 0;
}

#endif /* LIBHPDF_ASIAN_SUPPORT */
