// A fun sketch to demonstrate the use of the Tone library.
// By Brett Hagman
// bhagman@roguerobotics.com
// www.roguerobotics.com

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

// You can get more RTTTL (RingTone Text Transfer Language) songs from
// http://code.google.com/p/rogue-code/wiki/ToneLibraryDocumentation

#include <avr\pgmspace.h>
#include <avr\sleep.h>

#define BUTTON_PIN 2
#define TONE_PIN 9
#define SWITCH_PIN 13

#define SONGS_NUM 28

#define OCTAVE_OFFSET 0

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

const char song0[] PROGMEM = "ArabianN:d=16,o=6,b=63:8a#5,a#.5,c.,c#,4f.,32e,32f,8e,c#,c,c#.,c.,a#5,4f.,32e,32f,8e,c#,c#.,c.,a#5,8f.,f,g#.,f.,d#,8f.,32c#,32f,e.,c#.,e,2f";
const char song1[] PROGMEM = "TheyDont:d=4,o=5,b=125:16f,16e,16f,16e,16f,16e,8d,16e,16d,16e,16d,16e,16d,16c,16d,d,1p,16f,16e,16f,16e,16f,16e,8d,16e,16d,16e,16d,16e,16d,16c,16d,d";
const char song2[] PROGMEM = "EarthSon:d=4,o=5,b=100:8c#6,8p,16d#7,16d#7,16c#7,16g#6,8a#6,8c#7,8a#6,8f#6,8c#6,8p,16d#7,16c#7,16g#6,8a#6,8c#7,8a#6,8f#6,8c#6,8p,16d#7,16d#7,16c#7,8g#6,8c#7,8a#6,8f#6,8g#6";
const char song3[] PROGMEM = "BlackOrW:d=8,o=6,b=125:32p,b5,e,g#,a,g#,e,b5,a5,g#5,a5,2b5,p,16b5,16b5,e,g#,a,g#,e,b5,a5,g#5,a5,4b.5,p,16b5,16b5,c#,16c#,e,16e,f#.,16e,e,p,16e,16e,c#,c#,e,e,f#,e,f#,4g#.";
const char song4[] PROGMEM = "Yolochka:d=8,o=5,b=100:c,a,a,g,a,f,c,c,c,a,a,a#,g,4c.6,c6d,d,a#,a#,a,g,f,f,a,a,g,a,4f.";
const char song5[] PROGMEM = "Benny Hill:d=16,o=5,b=125:8d.,e,8g,8g,e,d,a4,b4,d,b4,8e,d,b4,a4,b4,8a4,a4,a#4,b4,d,e,d,4g,4p,d,e,d,8g,8g,e,d,a4,b4,d,b4,8e,d,b4,a4,b4,8d,d,d,f#,a,8f,4d";
const char song6[] PROGMEM = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6";
const char song7[] PROGMEM = "JingleBe:d=8,o=6,b=125:e,e,e.,16d#,e,e,e.,16d#,e,g,c.,16d,2e,f,f,f.,16f,f,e,e,16e,16e,e,d,d,e,2d";
const char song8[] PROGMEM = "WeWishYo:d=4,o=6,b=35:16a5,16d6,32d6,32e6,32d6,32c#6,16b5,16g5,16b5,16e6,32e6,32f#6,32e6,32d6,16c#6,16a5,16c#6,16f#6,32f#6,32g6,32f#6,32e6,16d6,16b5,16a5,16b5,16e6,16c#6,8d6";
const char song9[] PROGMEM = "WeddingM:d=4,o=5,b=90:d,16g,8p,16g,g,p,d,8a,16p,16f#,g,p,d,8g,16p,16b,d6,8b,16p,16g,e,16a,8p,16b,g";
const char song10[] PROGMEM = "4Seasons:d=16,o=6,b=120:8e,8g#,8g#,8g#,f#,e,4b.,b,a,8g#,8g#,8g#,f#,e,4b.,b,a,8g#,a,b,8a,8g#,8f#,8d#,4b.";
const char song11[] PROGMEM = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
const char song12[] PROGMEM = "Sherlock:d=4,o=6,b=100:4f.5,16f5,a5,c6,16f6,16e6,16d6,16e6,f.6,e6,8d6,16c6,16a#5,16a5,16a#5,8c6,16c6,16c6,8c6,a#5,8a5,2a5"; 
const char song13[] PROGMEM = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
const char song14[] PROGMEM = "FurElise:d=8,o=5,b=125:32p,e6,d#6,e6,d#6,e6,b,d6,c6,4a.,32p,c,e,a,4b.,32p,e,g#,b,4c.6,32p,e,e6,d#6,e6,d#6,e6,b,d6,c6,4a.,32p,c,e,a,4b.,32p,d,c6,b,2a";
const char song15[] PROGMEM = "TurkishMa:d=4,o=6,b=160:16e,16d5,16c#,16d,8f,8p,16g,16f,16e,16f,8a,8p,16a#,16a,16g#,16a,16e7,16d7,16c#7,16d7,16e7,16d7,16c#7,16d7,f7,8d7,8f7,8e7,8d7,8c7,8d7,8e7,8d7,8c7,8d7,8e7,8d7,8c7,8b,a";
const char song16[] PROGMEM = "OdeToJoy:d=4,o=6,b=100:a5,a5,a#5,c,c,a#5,a5,g5,f5,f5,g5,a5,a.5,8g5,2g5,a5,a5,a#5,c,c,a#5,a5,g5,f5,f5,g5,a5,g.5,8f5,2f5";
const char song17[] PROGMEM = "Khutor:d=8,o=6,b=125:e,e,e,e,4d,e,f,2e,4p.,g,g,g,g,e,4f,g,f,2e,2p";
const char song18[] PROGMEM = "Moscow:d=8,o=6,b=100:4f#,4g#,b,a,4e.,4b5,a5,e.,16d,2f,g,f,4e,d,c,4e,4d,2a.5";
const char song19[] PROGMEM = "Moscow2:d=4,o=6,b=100:8c7,c.7,8b,b.,8b,8b,8a,8b,8c7,a,8p,8c7,c.7,8b,8b,8a,8b,8c7,a,p,p,p";
const char song20[] PROGMEM = "Vodyanoy:d=8,o=6,b=100:p,f,e,d,2b,p,e,d,c,2a,p,c,b5,a5,4f.,g#5,a5,a5,2p.";
const char song21[] PROGMEM = "Schastye:d=4,o=5,b=125:a,a,a,a,8a,a#,8d,2c#,g,g,g,g,8g,a,8c#,2d";
const char song22[] PROGMEM = "Zaytsy:d=4,o=5,b=175:2a,2c6,a,8a,2e.,2a,2c6,a,8a,2f.,2d,2f,e,8e,2b4.,e,d,c,d,1e";
const char song23[] PROGMEM = "Medvedi:d=4,o=5,b=175:d,8d,8f,a,d,e,e,2p,c#,8c#,8e,a,c#,d,2p.,d,8d,8f,a,d,e,e,2p,g,f,e,g,2a.,p";
const char song24[] PROGMEM = "Serdtse:d=8,o=5,b=120:f,g,a,f,d,b4,a4,a4,f.,16c#,d.,16a4,4a4,4p,f,g,4a.,a,a#,f,f,a#,2c6";
const char song25[] PROGMEM = "Gena:d=8,o=5,b=150:g,g#,4g,c,d,d#,c,g,g#,4g,d,d#,f,d,g,g#,4g,d,d#,4d,g,g#,2g.";
const char song26[] PROGMEM = "Oblaka:d=4,o=5,b=175:c,f,g#,1c6,4p,c#6,c6,c#6,c6,a#,g#,c6,4g";
const char song27[] PROGMEM = "Mushketery:d=8,o=6,b=125:g5,e,e,e,e,e,d,d,16e,d.,c,b5,16c,e.5,p,e5,c,a5,c,16d,e.,16d,c.,e,d,e,d,16a5,d."; 

const char* const songs[] PROGMEM = {song0,song1,song2,song3,song4,song5,song6,song7,song8,song9,song10,song11,song12,song13,song14};
char buffer[450];
long songnumber = 0;

void setup(void)
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(SWITCH_PIN, OUTPUT);
}

#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(char *p)
{
    // Absolutely no error checking in here
    
    byte default_dur = 4;
    byte default_oct = 6;
    int bpm = 63;
    int num;
    long wholenote;
    long duration;
    byte note;
    byte scale;

    // format: d=N,o=N,b=NNN:
    // find the start (skip name, etc)

    while(*p != ':') p++;                   // ignore name
    p++;                                    // skip ':'

    // get default duration
    if(*p == 'd')
    {
        p++; p++;                           // skip "d="
        num = 0;
        while(isdigit(*p))
        {
            num = (num * 10) + (*p++ - '0');
        }
        if(num > 0) default_dur = num;
        p++;                                // skip comma
    }

    // get default octave
    if(*p == 'o')
    {
        p++; p++;                           // skip "o="
        num = *p++ - '0';
        if(num >= 3 && num <=7) default_oct = num;
        p++;                                // skip comma
    }

    // get BPM
    if(*p == 'b')
    {
        p++; p++;                           // skip "b="
        num = 0;
        while(isdigit(*p))
        {
            num = (num * 10) + (*p++ - '0');
        }
        bpm = num;
        p++;                                // skip colon
    }

    // BPM usually expresses the number of quarter notes per minute
    wholenote = (60 * 1000L / bpm) * 4;     // this is the time for whole note (in milliseconds)
    
    
    // now begin note loop
    while(*p)
    {
        // first, get note duration, if available
        num = 0;
        while(isdigit(*p))
        {
            num = (num * 10) + (*p++ - '0');
        }
        
        if(num) duration = wholenote / num;
        else duration = wholenote / default_dur;    // we will need to check if we are a dotted note after

        // now get the note
        note = 0;

        switch(*p)
        {
            case 'c':
                note = 1;
                break;
            case 'd':
                note = 3;
                break;
            case 'e':
                note = 5;
                break;
            case 'f':
                note = 6;
                break;
            case 'g':
                note = 8;
                break;
            case 'a':
                note = 10;
                break;
            case 'b':
                note = 12;
                break;
            case 'p':
            default:
                note = 0;
        }
        p++;

        // now, get optional '#' sharp
        if(*p == '#')
        {
            note++;
            p++;
        }

        // now, get optional '.' dotted note
        if(*p == '.')
        {
            duration += duration/2;
            p++;
        }
    
        // now, get scale
        if(isdigit(*p))
        {
            scale = *p - '0';
            p++;
        }
        else
        {
            scale = default_oct;
        }

        scale += OCTAVE_OFFSET;

        if(*p == ',')
            p++;                        // skip comma for next note (or we may be at the end)

        // now play the note

        if(note)
        {
            tone(TONE_PIN, notes[(scale - 4) * 12 + note]);
            delay(duration);
            noTone(TONE_PIN);
        }
        else
        {
            delay(duration);
        }
    }
}

void wakeUpNow()
{
}

void loop(void)
{
    sleep_enable();
    attachInterrupt(0, wakeUpNow, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();
    sleep_bod_disable();
    sei();
    sleep_cpu();
    /* wake up here */
    sleep_disable();

    digitalWrite(SWITCH_PIN, HIGH);
    strcpy_P(buffer, (char*)pgm_read_word(&(songs[songnumber])));
    play_rtttl(buffer);
    digitalWrite(SWITCH_PIN, LOW);
    songnumber = (songnumber + 1) % SONGS_NUM;
}
