#ifndef FRAME_H
#define FRAME_H

typedef struct frame
{
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;

} frame;

/**
 * creates a frame from a string of form XxY+W+H
 * @param string : a string of form  XxY+W+H
 * @return a pointer to a frame, must be deallocated
 */
frame *frame__from_str(const char *string);

/**
 * transforms a frame into a string of form XxY,WxH
 * @param frame : a pointer to a frame
 * @return a pointer to a string of form XxY,WxH, must be deallocated
 */
 char *frame__to_str(const frame *frame);

/**
 * checks if a frame 'viewer' contains another frame 'snippet'
 * @param viewer : a frame representing the viewer or aquarium
 * @param snippet : a frame representing a fish
 * @return 1 if viewer contains snippet and 0 if not
 */
int frame__includes_snippet(const frame *viewer, const frame *snippet);

/**
 * changes snippet x and y attributes randomly inside viewer
 * @param snippet : frame representing the fish
 * @param viewer : frame representing the aquarium
 */
 void frame__move_randomly_inside(frame *snippet, const frame *viewer);

/**
 * converts a relative frame to an absolute frame
 * @param snippet : frame representing the fish
 * @param viewer : frame representing the viewer
 * @return a pointer to an allocated absolute frame, needs to be freed
 */
frame *frame__get_absolute(const frame *snippet, const frame *viewer);

/**
 * converts an absolute frame to a relative frame
 * @param snippet : frame representing the fish
 * @param viewer : frame representing the viewer
 * @return a pointer to an allocated relative frame, needs to be freed
 */
frame *frame__get_relative(const frame *snippet, const frame *viewer);

#endif //FRAME_H
