// C++ implementation of the Blue Robotics 'Ping' binary message protocol

//~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
// THIS IS AN AUTOGENERATED FILE
// DO NOT EDIT
//~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!

#pragma once

/// PingMessage objects provide a wrapper over vector
/// for convenient access and packing of field data
///
/// These files are generated by the ping_generator.py
/// script found in this directory

#ifdef QT_CORE_LIB
#include <QObject>

#endif
namespace Ping1DNamespace {
#ifdef QT_CORE_LIB
    Q_NAMESPACE
#endif
    enum msg_ping1D_id {
        Ack = 1,
        Ascii_text = 3,
        Continuous_start = 1400,
        Continuous_stop = 1401,
        Device_id = 1201,
        Distance = 1212,
        Distance_simple = 1211,
        Firmware_version = 1200,
        Gain_index = 1207,
        General_info = 1210,
        Goto_bootloader = 1100,
        Mode_auto = 1205,
        Nack = 2,
        Pcb_temperature = 1214,
        Ping_enable = 1215,
        Ping_interval = 1206,
        Processor_temperature = 1213,
        Profile = 1300,
        Protocol_version = 5,
        Pulse_duration = 1208,
        Range = 1204,
        Set_device_id = 1000,
        Set_gain_index = 1005,
        Set_mode_auto = 1003,
        Set_ping_enable = 1006,
        Set_ping_interval = 1004,
        Set_range = 1001,
        Set_speed_of_sound = 1002,
        Speed_of_sound = 1203,
        Undefined = 0,
        Voltage_5 = 1202,
    };
#ifdef QT_CORE_LIB
    Q_ENUM_NS(msg_ping1D_id)
#endif
};

class PingMessage
{
public:
    PingMessage() : msgData { nullptr } {}

    PingMessage(const PingMessage &msg)
        : _bufferLength { msg.msgDataLength() }
        , msgData { (uint8_t*)malloc(sizeof(uint8_t) * _bufferLength) }
    {
        memcpy(msgData, msg.msgData, _bufferLength);
    }

    PingMessage(const uint16_t bufferLength)
        : _bufferLength { bufferLength }
        , msgData { (uint8_t*)malloc(sizeof(uint8_t) * _bufferLength) }
    {}

    PingMessage(const uint8_t* buf, const uint16_t length)
        : _bufferLength { length }
        , msgData { (uint8_t*)malloc(sizeof(uint8_t) * _bufferLength) }
    {
        memcpy(msgData, buf, _bufferLength);
    }

    PingMessage& operator = (const PingMessage &msg) {
        _bufferLength = msg.msgDataLength();
        if(msgData) free(msgData);
        msgData = (uint8_t*)malloc(sizeof(uint8_t) * _bufferLength);
        memcpy(msgData, msg.msgData, _bufferLength);
        return *this;
    }

    ~PingMessage() { if(msgData) free(msgData); }

protected:
    uint16_t _bufferLength;

public:
    uint8_t* msgData;
    uint16_t bufferLength() const { return _bufferLength; }; // size of internal buffer allocation
    uint16_t msgDataLength() const { return headerLength + payload_length() + checksumLength; }; // size of entire message buffer (header, payload, and checksum)

    uint16_t   payload_length()                const { return *(uint16_t*)(msgData + 2); } // This is ok only because alignment is static
    uint16_t   message_id()                    const { return *(uint16_t*)(msgData + 4); } // This is ok only because alignment is static
    uint8_t    src_device_id()                 const { return *(msgData + 6); }
    uint8_t    dst_device_id()                 const { return *(msgData + 7); }
    uint8_t*   payload_data(int offset=0)      const { return (msgData + 8 + offset); }
    uint16_t   checksum()                      const { return *(uint16_t*)(msgData + msgDataLength() - checksumLength); }

    static const uint8_t headerLength = 8;
    static const uint8_t checksumLength = 2;

    bool verifyChecksum() const {
        if(msgDataLength() > bufferLength()) {
            return false;
        }
        return checksum() == calculateChecksum();
    }

    void updateChecksum() {
        *(uint16_t*)(msgData + msgDataLength() - checksumLength) = calculateChecksum();
    }

    uint16_t calculateChecksum() const {
        uint16_t checksum = 0;

        if(msgDataLength() <= bufferLength()) {
            for(uint32_t i = 0, data_size = msgDataLength() - checksumLength; i < data_size; i++) {
                checksum += static_cast<uint8_t>(msgData[i]);
            }
        }

        return checksum;
    }
};

class ping_msg_ping1D_empty : public PingMessage
{
public:
    ping_msg_ping1D_empty(const PingMessage& msg) : PingMessage { msg } {}
    ping_msg_ping1D_empty(const uint8_t* buf, const uint16_t length) : PingMessage { buf, length } {}
    ping_msg_ping1D_empty()
        : PingMessage { 8 + 2 }
    {
        msgData[0] = 'B';
        msgData[1] = 'R';
        (uint16_t&)msgData[2] = 0; // payload size
        (uint16_t&)msgData[4] = 0; // ID
        msgData[6] = 0;
        msgData[7] = 0;
    }

    void set_id(const uint16_t id) { memcpy((msgData + 4 + 0), &id, 2); }
};
