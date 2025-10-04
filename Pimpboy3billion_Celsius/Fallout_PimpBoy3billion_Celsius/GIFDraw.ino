// Define colors for comparison and replacement
#define COLOR_GREEN   0x07E0  // RGB565 value for green
#define COLOR_WHITE   0xFFFF  // RGB565 value for white
#define COLOR_YELLOW  0xFFE0  // RGB565 value for yellow

// Define display width and height based on your TFT object
#define DISPLAY_WIDTH  tft.width()
#define DISPLAY_HEIGHT tft.height()

// Define the buffer size
#define BUFFER_SIZE 480  // Adjust size to your screen width or appropriate buffer

#ifdef USE_DMA
  uint16_t usTemp[2][BUFFER_SIZE]; // Global buffer to support DMA use
#else
  uint16_t usTemp[1][BUFFER_SIZE]; // Non-DMA buffer
#endif
bool dmaBuf = 0;  // Flag to toggle DMA buffer


void GIFDraw(GIFDRAW *pDraw)
{
    uint8_t *s;
    uint16_t *d, *usPalette;
    int x, y, iWidth, iCount;

    // Display bounds check and cropping
    iWidth = pDraw->iWidth;
    if (iWidth + pDraw->iX > DISPLAY_WIDTH)
        iWidth = DISPLAY_WIDTH - pDraw->iX;
    usPalette = pDraw->pPalette;
    y = pDraw->iY + pDraw->y; // current line
    if (y >= DISPLAY_HEIGHT || pDraw->iX >= DISPLAY_WIDTH || iWidth < 1)
        return;

    s = pDraw->pPixels;

    // Unroll the first pass to boost performance
    if (iWidth <= BUFFER_SIZE)
        for (iCount = 0; iCount < iWidth; iCount++) {
            uint16_t color = usPalette[*s++];

            // Check if the color is green or white and replace it with yellow
            if (color == COLOR_GREEN || color == COLOR_WHITE) {
                color = COLOR_YELLOW;  // Change to yellow
            }

            usTemp[dmaBuf][iCount] = color;
        }
    else
        for (iCount = 0; iCount < BUFFER_SIZE; iCount++) {
            uint16_t color = usPalette[*s++];

            // Check if the color is green or white and replace it with yellow
            if (color == COLOR_GREEN || color == COLOR_WHITE) {
                color = COLOR_YELLOW;  // Change to yellow
            }

            usTemp[dmaBuf][iCount] = color;
        }

#ifdef USE_DMA
    tft.dmaWait();
    tft.setAddrWindow(pDraw->iX, y, iWidth, 1);
    tft.pushPixelsDMA(&usTemp[dmaBuf][0], iCount);
    dmaBuf = !dmaBuf;
#else
    tft.setAddrWindow(pDraw->iX, y, iWidth, 1);
    tft.pushPixels(&usTemp[0][0], iCount);
#endif

    iWidth -= iCount;
    // Loop if pixel buffer smaller than width
    while (iWidth > 0)
    {
        if (iWidth <= BUFFER_SIZE)
            for (iCount = 0; iCount < iWidth; iCount++) {
                uint16_t color = usPalette[*s++];

                // Check if the color is green or white and replace it with yellow
                if (color == COLOR_GREEN || color == COLOR_WHITE) {
                    color = COLOR_YELLOW;  // Change to yellow
                }

                usTemp[dmaBuf][iCount] = color;
            }
        else
            for (iCount = 0; iCount < BUFFER_SIZE; iCount++) {
                uint16_t color = usPalette[*s++];

                // Check if the color is green or white and replace it with yellow
                if (color == COLOR_GREEN || color == COLOR_WHITE) {
                    color = COLOR_YELLOW;  // Change to yellow
                }

                usTemp[dmaBuf][iCount] = color;
            }

#ifdef USE_DMA
        tft.dmaWait();
        tft.pushPixelsDMA(&usTemp[dmaBuf][0], iCount);
        dmaBuf = !dmaBuf;
#else
        tft.pushPixels(&usTemp[0][0], iCount);
#endif
        iWidth -= iCount;
    }
}
