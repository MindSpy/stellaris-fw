#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vector>
#include "ADS1x9y.hpp"
#include "ProtocolWrapper.hpp"
#include "SensorDetector.hpp"
#include "TestSensor.hpp"

#define BLUETOOTH_STREAM Serial1
#define USB_STREAM Serial

/*!
 * Choose one stream for protocol buffers
 */
#define PB_STREAM BLUETOOTH_STREAM

class Device {
public:

    /*!
     * Prepare all device and peripherals.
     */
    Device();

    /*!
     * Destroy all create objects and instances.
     */
    ~Device();

    /*!
     * Prepare all sensors.
     */
    void SetupDevice();

    /*!
     * Prepare USB device.
     */
    void SetupUsb();

    /*!
     * Prepare Bluetooth device.
     */
    void SetupBluetooth();

    std::vector<sensor::Sensor*> sensor;

    SensorDetector* detector;
    ProtocolWrapper* protocol;

private:

    /*!
     * Tranfer speed for Bluetooth.
     * Maximum speed is for HC05 is 1382400=1.3Mbps
     */
    const static int BLUETOOTH_STREAM_BAUD = 921600;

    /*!
     * Init transfer speed fot Bluetooth.
     */
    const static int BLUETOOTH_STREAM_INIT_BAUD = 38400;

    /*!
     * Transfer speed for USB device.
     */
    const static int USB_STREAM_BAUD = 115200;
};
#endif // DEVICE_H
