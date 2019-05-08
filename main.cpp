#include <audio.hpp>
#include <iostream>
#include <unistd.h>

int main()
{
    ChipGen::Device dev = ChipGen::Device();
    ChipGen::Track track = ChipGen::Track("assets/birdland.wav");
    ChipGen::Listener lis = ChipGen::Listener();

    lis.setPosition(0, 0, 0);
    lis.setVelocity(0, 0, 0);
    float ori[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    lis.setOrientation(ori);

    //track.play();
    //track.setPosition(100.0, 0, 100.0);
    //track.setPitch(0.5);
    //track.setPosition(0, 0.5, 0.5);
    track.setVelocity(0, 0, 0);
    track.setGain(1.0);
    track.loop();
    
    do {
    } while (track.playing());

    return 0;
}
