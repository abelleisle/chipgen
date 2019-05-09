#include <audio.hpp>
#include <iostream>
#include <unistd.h>

#include <math.h>

int main()
{
    ChipGen::Device dev = ChipGen::Device();
    ChipGen::Track track = ChipGen::Track("assets/theme_jazz_mono.wav");
    ChipGen::Listener lis = ChipGen::Listener();

    lis.setGain(0.75f);
    lis.setPosition(0, 0, 0);
    lis.setVelocity(0, 0, 0);
    float ori[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    lis.setOrientation(ori);

    //track.play();
    //track.setPosition(100.0, 0, 100.0);
    //track.setPitch(0.5);
    track.setPosition(0.0f, 0.0f, 0.0f);
    track.setVelocity(0, 0, 0);
    track.setGain(1.0f);
    track.loop();

    float x = 0;
    float t = 0;
    
    do {
        x = 5*sin(t+=0.003);
        track.setPosition(x, 0, 1.0f);

        usleep(1000);
    } while (track.playing());

    return 0;
}
