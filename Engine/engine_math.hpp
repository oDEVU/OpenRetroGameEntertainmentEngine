#pragma once

namespace orgee
{
    double d_to_rad(double degree)
    {
        double pi = 3.14159265359;
        return (degree * (pi / 180));
    }
} // namespace orgee
