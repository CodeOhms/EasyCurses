/*
 * main.cpp
 *
 *      Author: Zac
 *     Contact: codeohms@protonmail.com
 *  Created on: 12 Sep. 2018
 */
#include <string>
#include <vector>

#include <memory>
#include <functional>

#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

#include "include/easyCurses.h"
using namespace EasyCurses;

void freeze()
{
    refresh();
    getch();
}

bool help()
{
    std::unique_ptr<WinData> hWinData(newWinData(stdscr));
    hWinData->height -= 1;
    WINDOW* helpWin = newwin(hWinData->height, hWinData->width, hWinData->startY, hWinData->startX);
    hWinData->win = helpWin;
    std::string helpText = "This is how to use the program:\n"\
    "ESC to exit\nENTER to select\n";
      for(unsigned i = 0; i < hWinData->height *2; ++i)
          helpText += "Blah blah blah\n";
    BasicMenu helpMenu(helpText, hWinData.get(), "BasicMenu demo");
    /*Stylise the menu borders*/
    //				borders => (bool, we, ns)
    helpMenu.setDrawBorder(true, 0, 0);
    flushinp();

    mvwprintw(stdscr, hWinData->height, 0, "Press ESC to exit menu");
    wrefresh(stdscr);

    helpMenu.menuLoop();
    delwin(helpWin);

    wmove(stdscr, hWinData->height, 0);
    wclrtoeol(stdscr);
    mvwprintw(stdscr, hWinData->height, 0, "Press h for help");
    wrefresh(stdscr);

    return true;
}

int main()
{
    initscr();
    noecho();
    curs_set(0);

    /*Begin BasicMenu demo*/
    std::string lines = { "Public Domain Curses, aka PDCurses, is an implementation of X/Open curses for multiple platforms. "\
        "Relative to the 'official' PDCurses project, this has a variety of improvements, adding a Windows GUI and a VT-like "\
        "console \"flavor\" of Curses and expanding the capabilities of the other flavors (SDL1, SDL2, X11, Win32 console, "\
        "OS/2, and DOS). Some details and screen shots at"\
        "\nhttps://www.projectpluto.com/win32a.htm"\
        "\nMuch of this was done during a long period in which 'official' PDCurses was inactive. It is hoped that the changes "\
        "in this fork can be merged into the 'official' PDCurses, and a pull request has been made. But the split is looking increasingly permanent."\
        "\n\nLegal Stuff"\
        "\nThe core package is in the public domain, but small portions of PDCurses are subject to copyright under various licenses. "\
        "Each directory contains a README file, with a section titled \"Distribution Status\" which describes the status of the files in that directory."\
        "\nIf you use PDCurses in an application, an acknowledgement would be appreciated, but is not mandatory. If you make corrections or "\
        "enhancements to PDCurses, please forward them to the current maintainer for the benefit of other users."
        "\nThis software is provided AS IS with NO WARRANTY whatsoever." };
    {
        std::unique_ptr<WinData> winData(newWinData(stdscr));
        WINDOW* demo = newwin(winData->height, winData->width, winData->startY, winData->startX);
        winData->win = demo;
        BasicMenu basicMenu(lines, winData.get(), "BasicMenu demo");
        /*Stylise the menu borders*/
        //				borders => (bool, we, ns)
        basicMenu.setDrawBorder(true, 0, 0);

        werase(demo);
        wrefresh(demo);

        flushinp();
        basicMenu.menuLoop();
    }

    /*Begin SelectionMenu demo*/
    {
        std::string options = {
        "camp\n1)The quick brown fox jumps over the lazy dog; and again, the quick brown fox jumps over the lazy dog; and once more, the quick brown fox jumps over the lazy dog\nSome very long text that should probably have better grammar not to mention it is running!\nashamed\ngold\nexist\nrhythm\nthumb\ncomplete\nheap\nradiate\nenchanted\nselective\nline\nexistence\nharbor\nugly\nrepresentative\nprick\npast\ninstrument\n2)Once more, the quick brown fox jumps over the lazy dog; and again, the quick brown fox jumps over the lazy dog; and once more, the quick brown fox jumps over the lazy dog\nfirst\nsister\nmetal\nvolleyball\ngrade\nreach\nspiteful\ncold\nultra\ngiddy\nsuggestion\ngorgeous\nencourage\nbed\njuice\nhelpless\nhum\numbrella\nscold\nfield\ntow\naspiring\nchildlike\nwoozy\nromantic\nconnect\npull\nalcoholic\nseparate\nsignal\ncuddly\nwonder\nspring\nfinger\nretire\nwar\nexultant\ntail\nlabored\nabnormal\ngrouchy\nsmoggy\ndam\nsecret\ninsect\nfumbling\nhumdrum\nill-fated\ntough\nfilm\nreduce\nrequest\nelbow\nhalting\ncamp\nlike\nwax\nrhetorical\ncurved\nheavenly\nairplane\ndoor\nreason\nscarf\nmarked\ncrush\nbridge\nharmony\nwreck\npretend\nplace\nambitious\nargument\nwatch\nhandsome\nabundant\nstormy\noffice\nwrap\norganic\nyarn\nconsolidate\ncandle\ncattle\nstrap\nplug\ndentist\nrecommendation\nlive\nmeeting\nsafe\nglove\nvertical\nbait\nfalse\ncolumn\ndeparture\nwidth\ncivilization\nindustry\nmourning\nsmall\nbiology\nperfume\nterms\nmole\nwarn\nparty\nprivacy\ninstall\nbirthday\ngreat\nthesis\nabcdefghijklmnopqrstuvwxyz\n" };

        std::unique_ptr<WinData> winData(newWinData(stdscr));
        winData->height -= 1;
        WINDOW* demo = newwin(winData->height, winData->width, winData->startY, winData->startX);
        winData->win = demo;

        mvwprintw(stdscr, winData->height, 0, "Press h for help");
        wrefresh(stdscr);

        SelectionMenu sMenu(options, winData.get(), "SelectionMenu demo");
        {
            std::map<unsigned, NavContent>& kB = sMenu.getKeyBindings();
            kB[104] = EasyCurses::NavContent::custom; //104 => 'h'
            sMenu.setKeyBindings(kB);
        }
        sMenu.setCustomAction(&help);
        /*Stylise the menu borders*/
        //				borders => (bool, we, ns)
        sMenu.setDrawBorder(true, 0, 0);

        int choice;
        werase(demo);
        wrefresh(demo);

        flushinp();
        sMenu.menuLoop();
        std::vector<unsigned> chosen;
        sMenu.getResult(chosen);

        //do something with option numbers returned
        werase(demo);
        mvwprintw(demo, 0, 0, "Options chosen:\n");
        for(auto option : chosen)
            wprintw(demo, "%i\n", option);
        wrefresh(demo);

        freeze();
        delwin(demo);
    } //User responsible for deleting window used


    /*Begin ttyProgressDialog demo*/
    {
        std::unique_ptr<WinData> winData2(newWinData(stdscr));
        WINDOW* demo2 = newwin(winData2->height, winData2->width, winData2->startY, winData2->startX);
        winData2->win = demo2;
        ttyProgressDialog dialog(winData2.get(), "ttyProgressDialog demo", "Task progress. press ESC to quit.");

        auto runDialog = [&] () -> void {
            dialog.dialog();

            for(double progress = 0.00; progress <= 100; progress += 25)
            {
                dialog.update(progress);
                Sleep(250);
            }
        };

        int input;
        wtimeout(demo2, 200);
        do
        {
            dialog.resetPBar();
            runDialog();
            input = wgetch(demo2);
        } while(input != 27); //27 == ESC key

        delwin(demo2);
    }

    endwin();
    return 0;
}
