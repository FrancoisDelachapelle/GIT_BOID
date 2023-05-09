#pragma once


struct FMinMaxSliderValuesFloat
{
    float min = 0;
    float max = 0;
    float current = 0;
    FMinMaxSliderValuesFloat(){}
    FMinMaxSliderValuesFloat(const float& _min, const float& _max, const float& _current)
    {
        min = _min;
        max = _max;
        current = _current;
    }
};


class AllGlobalStructs
{
public:
    
};
