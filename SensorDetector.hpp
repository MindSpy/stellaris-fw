#ifndef SENDORDETECTOR_HPP
#define SENDORDETECTOR_HPP

#include <vector>
#include "Sensor.hpp"
#include "Sensors.hpp"

namespace mindspy {

namespace sensor {

/*!
 * The SensorDetector detection sensors.
 */
class SensorDetector : public Sensors {
public:

    /*!
     * Prepare all sensors in container and
     * allocate memory for sensor.
     */
    SensorDetector();

    /*!
     * Remove all sensors in container and
     * deallocate memory for sensor.
     */
    ~SensorDetector();

    /*!
     * Count register sensors.
     * \return return number of sensors registered.
     */
    size_t count();

    /*!
     * This operator [] acces the member.
     * \param idx index of the memeber to access.
     * \return idx-th memeber.
     */
    mindspy::sensor::Sensor*& operator[](const size_t idx);

    /*!
     * Begin iterate item.
     * \return iterator for first item.
     */
    iterator begin();

    /*!
     * End iterate item.
     * \return iterator for last item.
     */
    iterator end();

private:

    /*!
     * Container for sensors.
     */
    container sensors;
};

} // namespace

} // namespace

#endif // SENDORDETECTOR_H