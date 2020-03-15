class ModeClock : public ModeBase
{
private:
    // Config
    int red                 = 128;
    int green               = 128;
    int blue                = 128;

    int startTime           = 0;
    int endTime             = 0;

    int startBrightness     = 0;
    int endBrightness       = 128;

    // State
    bool long lastClockExecution;
    bool keep_light_on = false;
public:
    ModeClock() {}

    virtual void initialize() {
        clockOnPauseBrightness = 255;
        lastClockExecution = 0;
    }

    virtual void render() {
        if (ntpTimeSet) {
            // Get the number of seconds so far today
            int currentSec = now() % 86400;


            if (currentSec > startTime && currentSec < endTime) {
                keep_light_on = true
                float currentBrightness =  (currentSec - startTime) / (endTime - startTime);

                for (int i = 0; i < topNumLeds; i++){
                    ledString[i] = CRGB( red * currentBrightness + startBrightness, green * currentBrightness + startBrightness, blue * currentBrightness + startBrightness);
                }
            }
            else if (!keep_light_on){ //initially the light should be off till
                for (int i = 0; i < topNumLeds; i++){
                    ledString[i] = CRGB( 0, 0, 0);
                }
            }
            else if ()

    }

    virtual void applyConfig(JsonVariant& settings) {
//         if (settings.containsKey("Epoch")){
//             settings["Epoch"]  = currentEpochTime = settings["Epoch"] | currentEpochTime;
//             setTime(currentEpochTime);
//         }


        settings["Red"] = red = settings["Red"] | red;
        settings["Green"] = green = settings["Green"] | green;
        settings["Blue"] = blue = settings["Blue"] | blue;

        settings["startTime"] = startTime = settings["startTime"] | startTime;
        settings["endTime"] = endTime = settings["endTime"] | endTime;


        settings["startBrightness"] = startBrightness = settings["startBrightness"] | startBrightness;
        settings["endBrightness"] = endBrightness = settings["endBrightness"] | endBrightness;

        if (settings["set"]){
            settings["set"] = keep_light_on = false;
        }

    }
};