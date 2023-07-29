/* Expressions for 8x8 I2C Nose Matrix */

#define NOSE_EXPRESSION_COUNT 17
#define NOSE_EXPRESSION_FIRST 0
#define NOSE_EXPRESSION_LAST 16
#define NOSE_NORMAL 0
#define NOSE_ANIM_1 1
#define NOSE_ANIM_2 2
#define NOSE_ANIM_3 3
#define NOSE_ANIM_4 4
#define NOSE_HEART_BIG 5
#define NOSE_HEART_SMALL 6
#define NOSE_ANGRY_LEFT 7
#define NOSE_ANGRY_RIGHT 8
#define NOSE_CAROTS 9
#define NOSE_GLITCHED 10
#define NOSE_SURPRISED 11
#define NOSE_SAD_LEFT 12
#define NOSE_SAD_RIGHT 13
#define NOSE_HEART_BIG_FLIPPED 14
#define NOSE_HEART_SMALL_FLIPPED 15
#define NOSE_OVERHEAT 16

static const uint8_t PROGMEM
    nose_normal[] = {B00111100, B01111110, B01111110, B01111110, B01111110, B01111110, B01111110, B00111100},
    nose_anim1[] = {B00111100, B01111110, B01111110, B01111110, B01111110, B01111110, B00000000, B00000000},
    nose_anim2[] = {B00111100, B01111110, B01111110, B01111110, B00000000, B00000000, B00000000, B00000000},
    nose_anim3[] = {B00111100, B01111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000},
    nose_anim4[] = {B00111100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000},
    nose_heart_big[] = {B00000000, B00010000, B00111000, B01111100, B11111110, B11111110, B01101100, B00000000},
    nose_heart_small[] = {B00000000, B00000000, B00010000, B00111000, B01111100, B01101100, B00000000, B00000000},
    nose_angry1[] = {B00111100, B01111110, B01111110, B01111100, B01111001, B01110011, B01100110, B00001100},
    nose_angry2[] = {B00111100, B01111110, B01111110, B00111110, B10011110, B11001110, B01100110, B00110000},
    nose_carots[] = {B00000000, B00000000, B00000000, B01000010, B01100110, B00111100, B00011000, B00000000},
    nose_glitched[] = {B00111110, B00111110, B00111110, B00111110, B00111110, B00111000, B00111000, B00111000},
    nose_surprised[] = {B00111100, B01000010, B10000001, B10000001, B10000001, B10000001, B01000010, B00111100},
    nose_sad1[] = {B00111100, B01111110, B01111110, B00111110, B00011110, B00001110, B00000110, B00000000},
    nose_sad2[] = {B00111100, B01111110, B01111110, B01111100, B01111000, B01110000, B01100000, B00000000},
    nose_heart_big_alt[] = {B00000000, B00001000, B00011100, B00111110, B01111111, B01111111, B00110110, B00000000},
    nose_heart_small_alt[] = {B00000000, B00000000, B00001000, B00011100, B00111110, B00110110, B00000000, B00000000},
    nose_overheat[] = {B11111111, B00100100, B00010010, B00100100, B01001000, B00100100, B00010010, B00100100},
    nose_error[] = {B01111110, B10111101, B11011011, B11100111, B11100111, B11011011, B10111101, B01111110};

static const uint8_t *getNoseExpression(uint8_t index)
{
    switch (index)
    {
    case NOSE_NORMAL:
        return nose_normal;
        break;
    case NOSE_ANIM_1:
        return nose_anim1;
        break;
    case NOSE_ANIM_2:
        return nose_anim2;
        break;
    case NOSE_ANIM_3:
        return nose_anim3;
        break;
    case NOSE_ANIM_4:
        return nose_anim4;
        break;
    case NOSE_HEART_BIG:
        return nose_heart_big;
        break;
    case NOSE_HEART_SMALL:
        return nose_heart_small;
        break;
    case NOSE_ANGRY_LEFT:
        return nose_angry1;
        break;
    case NOSE_ANGRY_RIGHT:
        return nose_angry2;
        break;
    case NOSE_CAROTS:
        return nose_carots;
        break;
    case NOSE_GLITCHED:
        return nose_glitched;
        break;
    case NOSE_SURPRISED:
        return nose_surprised;
        break;
    case NOSE_SAD_LEFT:
        return nose_sad1;
        break;
    case NOSE_SAD_RIGHT:
        return nose_sad2;
        break;
    case NOSE_HEART_BIG_FLIPPED:
        return nose_heart_big_alt;
        break;
    case NOSE_HEART_SMALL_FLIPPED:
        return nose_heart_small_alt;
        break;
    case NOSE_OVERHEAT:
        return nose_overheat;
        break;
    default:
        // This returns a special bitmap to indicate that somehow our code
        // has requested an invalid expression. The expression should look
        // like an inverted X
        return nose_error;
        break;
    }
}