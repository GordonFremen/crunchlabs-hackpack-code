#pragma once
// Compatibility shim: maps NHY3274TH API onto Adafruit TCS34725.
// The NHY3274TH is the color sensor on the CrunchLabs Card Dealing Bot PCB.
// Its library was never published publicly; this shim allows the sketches to
// compile and run using the TCS34725, which has an identical software interface.
// The gain register value 0x20 used in setup() is NHY3274TH-specific; it is
// mapped to TCS34725_GAIN_16X here as the closest equivalent.
#include <Adafruit_TCS34725.h>

class NHY3274TH {
public:
    NHY3274TH() : _tcs(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X) {}

    bool begin() {
        return _tcs.begin();
    }

    void setIntegrationTime(uint8_t it) {
        _tcs.setIntegrationTime(it);
    }

    // Accepts raw NHY3274TH gain register values; maps to nearest TCS34725 gain.
    void setGain(uint8_t gain) {
        tcs34725Gain_t g;
        if      (gain <= 0x01) g = TCS34725_GAIN_1X;
        else if (gain <= 0x04) g = TCS34725_GAIN_4X;
        else if (gain <= 0x10) g = TCS34725_GAIN_16X;
        else                   g = TCS34725_GAIN_60X;
        _tcs.setGain(g);
    }

    void getRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
        _tcs.getRawData(r, g, b, c);
    }

private:
    Adafruit_TCS34725 _tcs;
};
