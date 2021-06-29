//
// Created by Eric Yan on 2021/6/29.
//

#include <ostream>

////@preset: (x0, y0) is the origin of the line, (x1, y1) is the terminal of the line
////@input: 4 integers x0, y0, x1, y1
////@output: print the coordinates of the points to be drew
void Bresenham_line(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    double k = 1.0 * dy / dx;
    double e = 0.0;

    int y = y0;

    for (int x = x0; x <= x1; x++) {
        printf("%d %d\n", x, y);
        e += k;
        if (e >= 0.5) {
            e -= 1;
            y++;
        }
    }
}

////@preset: (x0, y0) is the origin of the line, (x1, y1) is the terminal of the line
////@restriction: no float point calculation
////@input: 4 integers x0, y0, x1, y1
////@output: print the coordinates of the points to be drew
void Bresenham_line_int(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int two_times_dx = dx << 1;
    int two_times_dy = dy << 1;
    int k = two_times_dy;
    int e = 0;

    int y = y0;

    for (int x = x0; x <= x1; x++) {
        printf("%d %d\n", x, y);
        e += k;
        if (e >= dx) {
            e -= two_times_dx;
            y++;
        }
    }
}