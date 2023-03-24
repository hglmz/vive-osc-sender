// LIGHTHOUSETRACKING.h
#ifndef _LIGHTHOUSETRACKING_H_
#define _LIGHTHOUSETRACKING_H_

// OpenVR
#include <openvr.h>
#include "ip\UdpSocket.h"
#include "osc\OscOutboundPacketStream.h"
#include "samples\shared\Matrices.h"
#include "FreeD.h"

class LighthouseTracking {
private:

    FreeD m_freed;

    // Basic stuff
    vr::IVRSystem* m_pHMD = NULL;
    vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
    bool m_deviceConnected[vr::k_unMaxTrackedDeviceCount];
    Matrix4 m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];

    // Position and rotation of pose
    vr::HmdVector3_t LighthouseTracking::GetPosition(vr::HmdMatrix34_t matrix);
    vr::HmdQuaternion_t LighthouseTracking::GetRotation(vr::HmdMatrix34_t matrix);

    // UdpTransmitSocket
    UdpTransmitSocket transmitSocket;

    // IpEndpointName
    IpEndpointName m_ip;

public:
    ~LighthouseTracking();
    LighthouseTracking(IpEndpointName ip);

    void setEndpoint(const char* ip_address, int port);

    // Main loop that listens for openvr events and calls process and parse routines, if false the service has quit
    bool RunProcedure();

    // Process a VR event and print some general info of what happens
    bool ProcessVREvent(const vr::VREvent_t& event);

    // Parse a tracking frame and print its position / rotation / events.
    void ParseTrackingFrame();

    // prints information of devices
    void PrintDevices();
};

inline void LighthouseTracking::setEndpoint(const char* ip_address, int port)
{
    m_ip = IpEndpointName(ip_address, port);
}

#endif _LIGHTHOUSETRACKING_H_
