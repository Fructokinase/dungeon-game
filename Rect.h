#ifndef __RECT_H_
#define __RECT_H_

struct Rect{
    int x1, y1;
    int x2, y2;
};

// bool isOverlapping(Rect r1, Rect r2) {

//     if(r2.x1 >= r1.x1) {
//         return (r2.x1 <= r1.x2) && (r2.y1  <= r1.y2);
//     } else {
//         return (r1.x1 <= r2.x2) && (r1.y1  <= r2.y2);
//     }
// }

#endif
