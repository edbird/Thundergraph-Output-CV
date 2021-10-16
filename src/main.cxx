
/******************************************************************/
/* COPYRIGHT: E.C. BIRDSALL, MARCH 2016                           */
/******************************************************************/

// useful websites
// cplusplus.com/en.cppreference
// learncpp.com
// en.cppreference.com

// additional useful references
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// http://stats.stackexchange.com/questions/6534/how-do-i-calculate-a-weighted-standard-deviation-in-excel
// https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
// http://www.etechplanet.com/codesnippets/computer-graphics-draw-a-line-using-bresenham-algorithm.aspx

// axis functions http://www.realtimerendering.com/resources/GraphicsGems/gems/Label.c

#include "THUNDERBIRD"

//#define DO_C1
//#define DO_C2
//#define DO_C3
//#define DO_C4
//#define DO_C5
//#define DO_C6
//#define DO_C7
//#define DO_C8
#define DO_C9

#include <random>
#include <cmath>
#include <iostream>

// TODO: error with box drawing frame around graph, rhs
// axis label background is 1 pixel too long at end, and same with font char blits
// axis label background offset is wrong. q (etc) touches floor

// TODO: character transformation
// rotation, mirroring/flip, color key clip/color map
// should all be different processes applied sequentially
// to avoid large number of functions required

// TODO: new class abstraction: FontGraphicsIOSurface -> a new class which thunder objects (eg; graph) can be drawn to

// TODO FIXME BUG: x axis only draws ticks (half-tick mode) for x > 0

int main()
{

    TB::g_current_font_type = TB::BMPFontType::XTERM_8_13_INV;


    /*
    TB::BMPIOSurface rotate_test("XTERM_6_13.bmp");
    rotate_test.Rotate90();
    rotate_test.SaveAs("rotated.bmp");
    rotate_test.Load("XTERM_6_13.bmp");
    rotate_test.Rotate180();
    rotate_test.SaveAs("rotated2.bmp");
    rotate_test.Load("XTERM_6_13.bmp");
    rotate_test.Rotate270();
    rotate_test.SaveAs("rotated3.bmp");

    std::cout << "rotate test done" << std::endl;
    */

    // TODO: this font is actually 13x5 size, the extra space is a stride of 1 bit
    // the others may be similarly defined

    TB::BMPIOSurface xterm_6_13("XTERM_6_13.bmp");

    TB::BMPIOSurface xterm_7_14("XTERM_7_14.bmp");
    TB::BMPIOSurface xterm_8_13("XTERM_8_13.bmp");
    TB::BMPIOSurface xterm_9_18("XTERM_9_18.bmp");
    TB::BMPIOSurface xterm_10_20("XTERM_10_20.bmp");


#ifdef DO_C1
    TB::BMPFontGraphicsIOSurface c(800, 600); //, 24); //"font_test.bmp"

    // default direction, default rotation
    c.PrintText(100, 300, "hello world"); //, false); // TODO: text direction, rotation
    c.PrintText(200, 400, "HELLO WORLD"); //, true);

    // 3 directions
    c.PrintText(200, 420, "VERTICAL UP", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::UP);
    c.PrintText(193, 420, "VERTICAL DOWN", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::DOWN);
    c.PrintText(186, 420, "REVERSE", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::REVERSE);

    // 0 deg rotations (cf below)
    c.PrintText(320, 200, "ROTATE 0", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::DEFAULT);
    c.PrintText(300, 220, "ROTATE 0 UP", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::UP);
    c.PrintText(300, 180, "ROTATE 0 DOWN", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::DOWN);
    c.PrintText(280, 200, "ROTATE 0 REVERSE", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::REVERSE);

    // 90 deg rotations
    c.PrintText(500, 320, "ROTATE 90", TB::BMPFontRotation::P90, TB::BMPFontDirection::DEFAULT);
    c.PrintText(480, 300, "ROTATE 90 UP", TB::BMPFontRotation::P90, TB::BMPFontDirection::UP);
    c.PrintText(520, 300, "ROTATE 90 DOWN", TB::BMPFontRotation::P90, TB::BMPFontDirection::DOWN);
    c.PrintText(500, 280, "ROTATE 90 REVERSE", TB::BMPFontRotation::P90, TB::BMPFontDirection::REVERSE);


    // combined (full string) rotations comparison

    // TODO: string rotation POV rather than per char
    c.PrintText(600, 400, "()STRING 0", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::DEFAULT);
    c.PrintText(600, 400, "()STRING 90", TB::BMPFontRotation::P90, TB::BMPFontDirection::DEFAULT);
    c.PrintText(600, 400, "()STRING 90", TB::BMPFontRotation::P180, TB::BMPFontDirection::DEFAULT);
    c.PrintText(600, 400, "()STRING 90", TB::BMPFontRotation::P270, TB::BMPFontDirection::DEFAULT);

    c.SaveAs("c.bmp");

    std::cout << "Finished c" << std::endl;
#endif


#ifdef DO_C2
    TB::BMPFontGraphicsIOSurface c2(1200, 900);

    // 0 deg rotations (cf below)
    c2.PrintText(320, 200, "ROTATE 0", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::DEFAULT);
    c2.PrintText(300, 220, "ROTATE 0 UP", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::UP);
    c2.PrintText(300, 180, "ROTATE 0 DOWN", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::DOWN);
    c2.PrintText(280, 200, "ROTATE 0 REVERSE", TB::BMPFontRotation::DEFAULT, TB::BMPFontDirection::REVERSE);

    // 90 deg rotations
    c2.PrintText(700, 220, "ROTATE 90", TB::BMPFontRotation::P90, TB::BMPFontDirection::DEFAULT);
    c2.PrintText(680, 200, "ROTATE 90 UP", TB::BMPFontRotation::P90, TB::BMPFontDirection::UP);
    c2.PrintText(720, 200, "ROTATE 90 DOWN", TB::BMPFontRotation::P90, TB::BMPFontDirection::DOWN);
    c2.PrintText(700, 180, "ROTATE 90 REVERSE", TB::BMPFontRotation::P90, TB::BMPFontDirection::REVERSE);

    // 180 deg rotations
    c2.PrintText(680, 600, "ROTATE 180", TB::BMPFontRotation::P180, TB::BMPFontDirection::DEFAULT);
    c2.PrintText(700, 580, "ROTATE 180 UP", TB::BMPFontRotation::P180, TB::BMPFontDirection::UP);
    c2.PrintText(700, 620, "ROTATE 180 DOWN", TB::BMPFontRotation::P180, TB::BMPFontDirection::DOWN);
    c2.PrintText(720, 600, "ROTATE 180 REVERSE", TB::BMPFontRotation::P180, TB::BMPFontDirection::REVERSE);

    // 270 deg rotations
    c2.PrintText(300, 580, "ROTATE 270", TB::BMPFontRotation::P270, TB::BMPFontDirection::DEFAULT);
    c2.PrintText(320, 600, "ROTATE 270 UP", TB::BMPFontRotation::P270, TB::BMPFontDirection::UP);
    c2.PrintText(280, 600, "ROTATE 270 DOWN", TB::BMPFontRotation::P270, TB::BMPFontDirection::DOWN);
    c2.PrintText(300, 620, "ROTATE 270 REVERSE", TB::BMPFontRotation::P270, TB::BMPFontDirection::REVERSE);

    // TODO
    //c2.Print(textobject)

    c2.SaveAs("c2.bmp");

    std::cout << "Finished c2" << std::endl;
#endif


#ifdef DO_C3
    TB::BMPFontGraphicsIOSurface c3(600, 400);
    TB::BMPText t1("1234567890abcdefghijklmnopqrstuvwxyz", 20, 20);
    TB::BMPText t2("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 40, 40);
    t2.SetVertical();
    //TB::TBAxis a1; //(50, 50, 200, 50);
    //TB::TBAxis a2; //(50, 50, 50, 200);

    c3.Draw(t1);
    c3.Draw(t2);

    c3.SaveAs("c3.bmp");

    std::cout << "Finished c3" << std::endl;
#endif


#ifdef DO_C4
    //TB::TBGraph g(600, 400);
    TB::TBGraph g(800, 600);
    TB::BMPFontGraphicsIOSurface c4(1920, 1080);
    g.SetTitle("Example Sin Graph");
    g.SetSubtitle("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\1");
    g.SetXAxisText("x");
    g.SetYAxisText("sin(x)");

    // TODO: this is for testing only
    //TB::GraphData<double> d;
    //TB::ScatterGraphYError<double> *d{new TB::ScatterGraphYError<double>};
    TB::ScatterGraphYError<double> d(COLOR_BLUE);
    size_t c_max{21};
    const static double pi2{8.0 * std::atan(1.0)};
    for(size_t c{0}; c < c_max; ++ c)
    {
        double x{(double)c / (double)(c_max - 1)};
        double y{std::sin(pi2 * x)};
        double e{0.1};
        d.Add(x, y, e);
        //d.Add(x, y);
    }
    g.AddGraph(/***/ &d);

    TB::ScatterGraphYError<double> d1(COLOR_RED);
    c_max = 51;
    for(size_t c{0}; c < c_max; ++ c)
    {
        double x{(double)c / (double)(c_max - 1)};
        double y{0.75 * std::sin(pi2 * 3.0 * x / 2.0 - 1.666 * pi2)};
        double e{0.2};
        d1.Add(x, y, e);
    }
    g.AddGraph(&d1);

    c4.Draw(g);
    c4.SaveAs("c4_800_600_2.bmp");

    std::cout << "Finished c4" << std::endl;
#endif


#ifdef DO_C5
    TB::BMPFontGraphicsIOSurface c5(600, 400);

    TB::TBGraphMarker m1(TB::TBGraphMarkerType::PIXEL, 10, 10, 4, TB::COLOR_RED);
    TB::TBGraphMarker m2(TB::TBGraphMarkerType::SQUARE, 20, 10, 4, TB::COLOR_ORANGE);
    TB::TBGraphMarker m3(TB::TBGraphMarkerType::SQUARE45, 30, 10, 4, TB::COLOR_YELLOW);
    TB::TBGraphMarker m4(TB::TBGraphMarkerType::CUBE1, 40, 10, 4, TB::COLOR_GREEN);
    TB::TBGraphMarker m5(TB::TBGraphMarkerType::CUBE2, 50, 10, 4, TB::COLOR_CYAN);
    TB::TBGraphMarker m6(TB::TBGraphMarkerType::DIAMOND1, 60, 10, 4, TB::COLOR_BLUE);
    TB::TBGraphMarker m7(TB::TBGraphMarkerType::DIAMOND2, 70, 10, 4, TB::COLOR_PURPLE);
    TB::TBGraphMarker m8(TB::TBGraphMarkerType::CIRCLE, 80, 10, 4, TB::COLOR_RED);
    TB::TBGraphMarker m9(TB::TBGraphMarkerType::ELIPSE1, 90, 10, 4, TB::COLOR_RED);
    TB::TBGraphMarker m10(TB::TBGraphMarkerType::ELIPSE2, 100, 10, 4, TB::COLOR_RED);
    TB::TBGraphMarker m11(TB::TBGraphMarkerType::PLUS, 110, 10, 4, TB::COLOR_RED);
    TB::TBGraphMarker m12(TB::TBGraphMarkerType::X, 120, 10, 4, TB::COLOR_RED);

    c5.Draw(m1);
    c5.Draw(m2);
    c5.Draw(m3);
    c5.Draw(m4);
    c5.Draw(m5);
    c5.Draw(m6);
    c5.Draw(m7);
    c5.Draw(m8);
    c5.Draw(m9);
    c5.Draw(m10);
    c5.Draw(m11);
    c5.Draw(m12);

    TB::TBGraphMarker mm1(TB::TBGraphMarkerType::PIXEL,    40,   60, 20, TB::COLOR_RED);
    TB::TBGraphMarker mm2(TB::TBGraphMarkerType::SQUARE,   90,   60, 20, TB::COLOR_ORANGE);
    TB::TBGraphMarker mm3(TB::TBGraphMarkerType::SQUARE45, 140,  60, 20, TB::COLOR_YELLOW);
    TB::TBGraphMarker mm22(TB::TBGraphMarkerType::SQUARE45, 90,  60, 20, TB::COLOR_BLACK);
    TB::TBGraphMarker mm4(TB::TBGraphMarkerType::CUBE1,    190,  60, 20, TB::COLOR_GREEN);
    TB::TBGraphMarker mm5(TB::TBGraphMarkerType::CUBE2,    240,  60, 20, TB::COLOR_CYAN);
    TB::TBGraphMarker mm6(TB::TBGraphMarkerType::DIAMOND1, 290,  60, 20, TB::COLOR_BLUE);
    TB::TBGraphMarker mm7(TB::TBGraphMarkerType::DIAMOND2,  40, 110, 20, TB::COLOR_PURPLE);
    TB::TBGraphMarker mm8(TB::TBGraphMarkerType::CIRCLE,    90, 110, 20, TB::COLOR_RED);
    TB::TBGraphMarker mm9(TB::TBGraphMarkerType::ELIPSE1,  140, 110, 20, TB::COLOR_RED);
    TB::TBGraphMarker mm10(TB::TBGraphMarkerType::ELIPSE2, 190, 110, 20, TB::COLOR_RED);
    TB::TBGraphMarker mm11(TB::TBGraphMarkerType::PLUS,    240, 110, 20, TB::COLOR_RED);
    TB::TBGraphMarker mm12(TB::TBGraphMarkerType::X,       290, 110, 20, TB::COLOR_RED);

    TB::TBGraphMarker mm13(TB::TBGraphMarkerType::SQUARE_NOFILL,    40, 160, 20, TB::COLOR_GREY10);
    TB::TBGraphMarker mm14(TB::TBGraphMarkerType::SQUARE45_NOFILL,  90, 160, 20, TB::COLOR_GREY20);
    TB::TBGraphMarker mm15(TB::TBGraphMarkerType::CUBE1_NOFILL,    140, 160, 20, TB::COLOR_GREY30);
    TB::TBGraphMarker mm16(TB::TBGraphMarkerType::CUBE2_NOFILL,    190, 160, 20, TB::COLOR_GREY40);
    TB::TBGraphMarker mm17(TB::TBGraphMarkerType::DIAMOND1_NOFILL, 240, 160, 20, TB::COLOR_GREY50);
    TB::TBGraphMarker mm18(TB::TBGraphMarkerType::DIAMOND2_NOFILL, 290, 160, 20, TB::COLOR_GREY60);
    TB::TBGraphMarker mm19(TB::TBGraphMarkerType::CIRCLE_NOFILL,    40, 210, 20, TB::COLOR_GREY70);
    TB::TBGraphMarker mm20(TB::TBGraphMarkerType::ELIPSE1_NOFILL,   90, 210, 20, TB::COLOR_GREY80);
    TB::TBGraphMarker mm21(TB::TBGraphMarkerType::ELIPSE2_NOFILL,  140, 210, 20, TB::COLOR_GREY90);

    TB::TBGraphMarker bigcirc(TB::TBGraphMarkerType::CIRCLE_NOFILL,  400, 250, 100, TB::COLOR_GREY50);


    c5.Draw(mm1);
    c5.Draw(mm2);
    c5.Draw(mm3);
    c5.Draw(mm4);
    c5.Draw(mm5);
    c5.Draw(mm6);
    c5.Draw(mm7);
    c5.Draw(mm8);
    c5.Draw(mm9);
    c5.Draw(mm10);
    c5.Draw(mm11);
    c5.Draw(mm12);

    c5.Draw(mm13);
    c5.Draw(mm14);
    c5.Draw(mm15);
    c5.Draw(mm16);
    c5.Draw(mm17);
    c5.Draw(mm18);
    c5.Draw(mm19);
    c5.Draw(mm20);
    c5.Draw(mm21);

    c5.Draw(mm22);

    c5.Draw(bigcirc);

    c5.SaveAs("c5.bmp");

    std::cout << "Finished c5" << std::endl;
#endif


#ifdef DO_C6

    //TB::GraphData<double> d;
    //size_t c_max{20};
    //for(size_t c{0}; c < c_max; ++ c)
    //{
    //    double x{(double)c / (double)c_max};
    //    double y{std::sin(x)}
    //    d.Add(x, y);
    //}

    TB::TBGraph g2(600, 400);
    //g.AddGraphData(d);

    TB::BMPFontGraphicsIOSurface c6(600, 400);

    c6.Draw(g2);

    c6.SaveAs("c6.bmp");

    std::cout << "Finished c6" << std::endl;

#endif

#ifdef DO_C7
    //TB::TBGraph g(600, 400);
    {
        TB::TBGraph g(800, 600);
        TB::BMPFontGraphicsIOSurface c7(800, 600);
        g.SetTitle("Example Sin Graph");
        g.SetSubtitle("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\1");
        g.SetXAxisText("x");
        g.SetYAxisText("sin(x)");

        TB::ScatterGraphYError<double> d(TB::COLOR_BLACK, TB::COLOR_BLUE);
        size_t c_max{21};
        const static double pi2{8.0 * std::atan(1.0)};
        for(size_t c{0}; c < c_max; ++ c)
        {
            double x{(double)c / (double)(c_max - 1)};
            double y{std::sin(pi2 * x)};
            double e{0.1};
            d.Add(x, y, e);
        }
        g.AddGraph(&d);

        TB::ScatterGraphYError<double> d1(TB::COLOR_BLACK, TB::COLOR_RED);
        c_max = 51;
        for(size_t c{0}; c < c_max; ++ c)
        {
            double x{(double)c / (double)(c_max - 1)};
            double y{0.75 * std::sin(pi2 * 3.0 * x / 2.0 - 1.666 * pi2)};
            double e{0.2};
            d1.Add(x, y, e);
        }
        g.AddGraph(&d1);

        c7.Draw(g);
        c7.SaveAs("c7.bmp");

        std::cout << "Finished c7" << std::endl;
    }
#endif

#ifdef DO_C8
    {
        TB::TBGraph g(800, 600);
        TB::BMPFontGraphicsIOSurface c8(800, 600);
        g.SetTitle("Example Histogram");
        //g.SetSubtitle("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\1");
        g.SetXAxisText("x");
        g.SetYAxisText("Random gaussian distributed data");

        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::normal_distribution<double> dis(5.0, 2.0);
        std::normal_distribution<double> dis2(3.0, 0.5);
        size_t n_max{10000000};

        TB::TBHistogram<double> d(0.0, 10.0, 100, TB::COLOR_ORANGE); //(TB::COLOR_BLACK, TB::COLOR_BLUE);// tests:
        //for(int i = 0; i < 100; ++ i)
        //{
        //    std::cout << "i=" << i << " l=" << d.get_bin_lowerbound(i) << " h=" << d.get_bin_upperbound(i) << " c=" << d.get_bin_center(i) << std::endl;
        //}
        d.SetFillStyle(TB::TBGraphFillStyle::HATCH); // try negative histos TODO
        d.SetFillSpacing(8);
        for(size_t n{0}; n < n_max; ++ n)
        {
            double x{dis(gen)};
            d.Fill(x);
        }
        g.AddGraph(&d);

        TB::TBFastHistogram<double> h(0.0, 10.0, 20, TB::COLOR_BLUE);
        h.SetFillStyle(TB::TBGraphFillStyle::HATCH);
        // tests:
        //for(int i = 0; i < 20; ++ i)
        //{
        //    std::cout << "i=" << i << " l=" << h.get_bin_lowerbound(i) << " h=" << h.get_bin_upperbound(i) << " c=" << h.get_bin_center(i) << std::endl;
        //}


        for(size_t n{0}; n < n_max / 20; ++ n)
        {
            double x{dis2(gen)};
            h.Fill(x);
        }
        g.AddGraph(&h);

        /*TB::ScatterGraphYError<double> d1(TB::COLOR_BLACK, TB::COLOR_RED);
        c_max = 51;
        for(size_t c{0}; c < c_max; ++ c)
        {
            double x{(double)c / (double)(c_max - 1)};
            double y{0.75 * std::sin(pi2 * 3.0 * x / 2.0 - 1.666 * pi2)};
            double e{0.2};
            d1.Add(x, y, e);
        }
        g.AddGraph(&d1);*/

        c8.Draw(g);
        c8.SaveAs("c8_dual.bmp");

        std::cout << "Finished c8" << std::endl;
    }
#endif

#ifdef DO_C9

    {
        TB::TBGraph g(800, 600);
        TB::BMPFontGraphicsIOSurface c9(800, 600);
        g.SetTitle("Example Histogram");
        //g.SetSubtitle("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\1");
        g.SetXAxisText("x");
        g.SetYAxisText("Random gaussian distributed data");

        std::random_device rd;
        std::mt19937_64 gen(0); //(rd());
        std::normal_distribution<double> dis(5.0, 2.0);
        //std::normal_distribution<double> dis2(3.0, 4.0 * 0.5);
        std::normal_distribution<double> dis2(3.0, 2.0);
        std::uniform_real_distribution<double> dis3(-1.0, 1.0);
        size_t n_max{10000000 / 100};

        TB::TBFastHistogram<double> d(0.0, 10.0, 10, TB::COLOR_ORANGE); //(TB::COLOR_BLACK, TB::COLOR_BLUE);// tests:
        //TB::TBFastHistogram<double> d(0.0, 10.0, 20, TB::COLOR_BLUE);
        //for(int i = 0; i < 100; ++ i)
        //{
        //    std::cout << "i=" << i << " l=" << d.get_bin_lowerbound(i) << " h=" << d.get_bin_upperbound(i) << " c=" << d.get_bin_center(i) << std::endl;
        //}
        d.SetFillStyle(TB::TBGraphFillStyle::HATCH); // try negative histos TODO
        d.SetFillSpacing(8);
        for(size_t n{0}; n < n_max; ++ n)
        {
            double x{dis(gen)};
            d.Fill(x);
        }
        //std::cout << "done fill" << std::endl;

        for(size_t ix{1}; ix <= d.GetNumBins(); ++ ix)
        {
            double v{dis3(gen)};
            //d.SetBinContent(ix, v); // NOT DRAWING WHOLE HISTOGRAM: FIXED?
            //std::cout << "setting bin content for " << ix << " to value " << v << std::endl;
        }

        g.AddGraph(&d);

        TB::TBHistogram<double> h(0.0, 10.0, 20, TB::COLOR_BLUE);
        h.SetFillStyle(TB::TBGraphFillStyle::HATCH);
        // tests:
        //for(int i = 0; i < 20; ++ i)
        //{
        //    std::cout << "i=" << i << " l=" << h.get_bin_lowerbound(i) << " h=" << h.get_bin_upperbound(i) << " c=" << h.get_bin_center(i) << std::endl;
        //}


        for(size_t n{0}; n < n_max; ++ n)
        {
            double x{dis2(gen)};
            h.Fill(x, -1.0); // note final line buggy FIXED
            // TODO: FILL FUNCTION DOES NOT WORK PROPERLY, GAUSSIAN IS OFFSET! FIXED?
            // TODO THERE ARE ONLY 19 BINS WHEN 20 REQUESTED! FIXED
        }
        g.AddGraph(&h);

        /*TB::ScatterGraphYError<double> d1(TB::COLOR_BLACK, TB::COLOR_RED);
        c_max = 51;
        for(size_t c{0}; c < c_max; ++ c)
        {
            double x{(double)c / (double)(c_max - 1)};
            double y{0.75 * std::sin(pi2 * 3.0 * x / 2.0 - 1.666 * pi2)};
            double e{0.2};
            d1.Add(x, y, e);
        }
        g.AddGraph(&d1);*/

        c9.Draw(g);

        //c9.DrawRectHatch(0, 300, 100, 200, TB::COLOR_PURPLE, 4, 3);

        int spacing{9};
        int width{29};

        // Note bug in histogram drawing code? Lines overlap at the x edges.
        // was: (spacing + 0 * width % spacing)

    /*
        c9.DrawAreaHatch(200 + 0 * width, 10, 200 + 1 * width - 1, 600, TB::COLOR_BLACK,  spacing, - 0 * width); // makes no difference to spacing - 0 * (width % spacing)
        c9.DrawAreaHatch(200 + 1 * width, 10, 200 + 2 * width - 1, 600, TB::COLOR_BLUE,   spacing, - 1 * width);
        c9.DrawAreaHatch(200 + 2 * width, 10, 200 + 3 * width - 1, 600, TB::COLOR_RED,    spacing, - 2 * width);
        c9.DrawAreaHatch(200 + 3 * width, 10, 200 + 4 * width - 1, 600, TB::COLOR_ORANGE, spacing, - 3 * width); // starts from 1 place lower
        c9.DrawAreaHatch(200 + 4 * width, 20, 200 + 5 * width - 1, 590, TB::COLOR_YELLOW, spacing, - 4 * width + 10); // starts from 1 place lower
        c9.DrawAreaHatch(200 + 5 * width, 40, 200 + 6 * width - 1, 580, TB::COLOR_GREEN,  spacing, - 5 * width + 30); // starts from 1 place lower
        c9.DrawAreaHatch(200 + 6 * width, 50, 200 + 7 * width - 1, 560, TB::COLOR_CYAN,   spacing, - 6 * width + 40);
        c9.DrawAreaHatch(200 + 7 * width, 55, 200 + 8 * width - 1, 550, TB::COLOR_BLUE,   spacing, - 7 * width + 45);
        c9.DrawAreaHatch(200 + 8 * width, 25, 200 + 9 * width - 1, 540, TB::COLOR_PURPLE, spacing, - 8 * width + 15);
    */

        c9.SaveAs("c9.bmp");

        std::cout << "Finished c9" << std::endl;
    }

#endif

    // TODO class conversion files
    // TODO: drawable text should be its own class, contain a string,
    // be centre origin or corner origin or side origin (9 origins)
    // ect


    //TB::BMPFile bmpfile("test.bmp");
    //bmpfile.SaveAs("test_out.bmp");

    //TB::BMPFile bmpfile2("test_out.bmp");

    return 0;

}
