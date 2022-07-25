#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

struct RemoteControl
{
    unsigned long lastCommandTime;

    void update() {}

    void newCommand()
};

#endif /* REMOTECONTROL_H */
