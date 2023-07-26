/* Expressions for 8x8 I2C Eye Matrix */

#define EYE_EXPRESSION_COUNT 17
#define EYE_EXPRESSION_FIRST 0
#define EYE_EXPRESSION_LAST 16
#define EYE_NORMAL 0
#define EYE_ANIM_1 1
#define EYE_ANIM_2 2
#define EYE_ANIM_3 3
#define EYE_ANIM_4 4
#define EYE_HEART_BIG 5
#define EYE_HEART_SMALL 6
#define EYE_ANGRY_LEFT 7
#define EYE_ANGRY_RIGHT 8
#define EYE_CAROTS 9
#define EYE_GLITCHED 10
#define EYE_SURPRISED 11
#define EYE_SAD_LEFT 12
#define EYE_SAD_RIGHT 13
#define EYE_HEART_BIG_FLIPPED 14
#define EYE_HEART_SMALL_FLIPPED 15
#define EYE_OVERHEAT 16

static const uint8_t PROGMEM
    eye_normal[] = {B00111100, B01111110, B01111110, B01111110, B01111110, B01111110, B01111110, B00111100},
    eye_anim1[] = {B00111100, B01111110, B01111110, B01111110, B01111110, B01111110, B00000000, B00000000},
    eye_anim2[] = {B00111100, B01111110, B01111110, B01111110, B00000000, B00000000, B00000000, B00000000},
    eye_anim3[] = {B00111100, B01111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000},
    eye_anim4[] = {B00111100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000},
    eye_heart_big[] = {B00000000, B00010000, B00111000, B01111100, B11111110, B11111110, B01101100, B00000000},
    eye_heart_small[] = {B00000000, B00000000, B00010000, B00111000, B01111100, B01101100, B00000000, B00000000},
    eye_angry1[] = {B00111100, B01111110, B01111110, B01111100, B01111001, B01110011, B01100110, B00001100},
    eye_angry2[] = {B00111100, B01111110, B01111110, B00111110, B10011110, B11001110, B01100110, B00110000},
    eye_carots[] = {B00000000, B00000000, B00000000, B01000010, B01100110, B00111100, B00011000, B00000000},
    eye_glitched[] = {B00111110, B00111110, B00111110, B00111110, B00111110, B00111000, B00111000, B00111000},
    eye_surprised[] = {B00111100, B01000010, B10000001, B10000001, B10000001, B10000001, B01000010, B00111100},
    eye_sad1[] = {B00111100, B01111110, B01111110, B00111110, B00011110, B00001110, B00000110, B00000000},
    eye_sad2[] = {B00111100, B01111110, B01111110, B01111100, B01111000, B01110000, B01100000, B00000000},
    eye_heart_big_alt[] = {B00000000, B00001000, B00011100, B00111110, B01111111, B01111111, B00110110, B00000000},
    eye_heart_small_alt[] = {B00000000, B00000000, B00001000, B00011100, B00111110, B00110110, B00000000, B00000000},
    eye_overheat[] = {B11111111, B00100100, B00010010, B00100100, B01001000, B00100100, B00010010, B00100100},
    error[] = {B01111110, B10111101, B11011011, B11100111, B11100111, B11011011, B10111101, B01111110};

static const uint8_t *getEyeExpression(uint8_t index)
{
    switch (index)
    {
    case EYE_NORMAL:
        return eye_normal;
        break;
    case EYE_ANIM_1:
        return eye_anim1;
        break;
    case EYE_ANIM_2:
        return eye_anim2;
        break;
    case EYE_ANIM_3:
        return eye_anim3;
        break;
    case EYE_ANIM_4:
        return eye_anim4;
        break;
    case EYE_HEART_BIG:
        return eye_heart_big;
        break;
    case EYE_HEART_SMALL:
        return eye_heart_small;
        break;
    case EYE_ANGRY_LEFT:
        return eye_angry1;
        break;
    case EYE_ANGRY_RIGHT:
        return eye_angry2;
        break;
    case EYE_CAROTS:
        return eye_carots;
        break;
    case EYE_GLITCHED:
        return eye_glitched;
        break;
    case EYE_SURPRISED:
        return eye_surprised;
        break;
    case EYE_SAD_LEFT:
        return eye_sad1;
        break;
    case EYE_SAD_RIGHT:
        return eye_sad2;
        break;
    case EYE_HEART_BIG_FLIPPED:
        return eye_heart_big_alt;
        break;
    case EYE_HEART_SMALL_FLIPPED:
        return eye_heart_small_alt;
        break;
    case EYE_OVERHEAT:
        return eye_overheat;
        break;
    default:
        // This returns a special bitmap that doesn't look like an eye
        // to indicate that somehow our code has requested an invalid
        // eye expression. The expression should look like an inverted X
        return error;
        break;
    }
}