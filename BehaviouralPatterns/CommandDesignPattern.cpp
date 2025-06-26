#include <bits/stdc++.h>
using namespace std;

class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {};
};

class Light
{
public:
    void on()
    {
        cout << "Light on" << endl;
    }
    void off()
    {
        cout << "Light off" << endl;
    }
};

class Fan
{
public:
    void on()
    {
        cout << "Fan on" << endl;
    }
    void off()
    {
        cout << "Fan off" << endl;
    }
};

// Concrete Command for Light
class LightCommand : public Command
{
private:
    Light *light;

public:
    LightCommand(Light *l)
    {
        light = l;
    }

    void execute()
    {
        light->on();
    }

    void undo()
    {
        light->off();
    }
};

// Concrete Command for Fan
class FanCommand : public Command
{
private:
    Fan *fan;

public:
    FanCommand(Fan *f)
    {
        fan = f;
    }
    void execute()
    {
        fan->on();
    }
    void undo()
    {
        fan->off();
    }
};

class RemoteController
{
private:
    static const int numButtons = 4;
    Command *buttons[numButtons];
    bool buttonPressed[numButtons];

public:
    RemoteController()
    {
        for (int i = 0; i < numButtons; i++)
        {
            buttons[i] = nullptr;
            buttonPressed[i] = false; // false = off, true = on
        }
    }

    void setCommand(int idx, Command *cmd)
    {
        if (idx >= 0 && idx < numButtons)
        {
            if (buttons[idx] != nullptr)
                delete buttons[idx];
            buttons[idx] = cmd;
            buttonPressed[idx] = false;
        }
    }

    void pressButton(int idx)
    {
        if (idx >= 0 && idx < numButtons && buttons[idx] != nullptr)
        {
            if (buttonPressed[idx] == false)
            {
                buttons[idx]->execute();
            }
            else
            {
                buttons[idx]->undo();
            }
            buttonPressed[idx] = !buttonPressed[idx];
        }
        else
        {
            cout << "No command assigned at button " << idx << endl;
        }
    }

    ~RemoteController()
    {
        for (int i = 0; i < numButtons; i++)
        {
            if (buttons[i] != NULL)
                delete buttons[i];
        }
    }
};

int main()
{
    Light *livingRoomLight = new Light();
    Fan *ceilingFan = new Fan();

    RemoteController *remote = new RemoteController();

    remote->setCommand(0, new LightCommand(livingRoomLight));
    remote->setCommand(1, new FanCommand(ceilingFan));

    // Simulate button presses (toggle behavior)
    cout << "--- Toggling Light Button 0 ---" << endl;
    remote->pressButton(0); // ON
    remote->pressButton(0); // OFF

    cout << "--- Toggling Fan Button 1 ---" << endl;
    remote->pressButton(1); // ON
    remote->pressButton(1); // OFF

    // Press unassigned button to show default message
    cout << "--- Pressing Unassigned Button 2 ---" << endl;
    remote->pressButton(2);

    // Clean up
    delete remote;
    delete livingRoomLight;
    delete ceilingFan;

    // cout << "Hello" << endl;

    return 0;
}