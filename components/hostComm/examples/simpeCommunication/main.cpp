/* ========================================================================================================================== */ /**
 @license    BSD 3-Clause
 @copyright  microHAL
 @version    $Id$
 @brief      board support package for stm32f4Discovery board

 @authors    Pawel Okas
 created on: 20-12-2014
 last modification: <DD-MM-YYYY>

 @copyright Copyright (c) 2014, microHAL
 All rights reserved.
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
 conditions are met:
 	 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 	 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
 	 	in the documentation and/or other materials provided with the distribution.
 	 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived
 	 	from this software without specific prior written permission.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */ /* ==========================================================================================================================
                                                                                                                                                                                                                                                                           */

#include "hostComm.h"
#include "microhal.h"
#include "microhal_bsp.h"

#include "testPacket.h"

using namespace microhal;
using namespace diagnostic;

using namespace std::literals::chrono_literals;

HostComm hostComm(communicationPort, debugPort);

volatile bool getTestRequest = false;

void proceedPacket(HostCommPacket &packet) {
    if (packet.getType() == testPacket::Request) {
        diagChannel << Debug << "Got testPacket request. Sending testPacket ...";

        getTestRequest = true;
    }

    if (packet.getType() == testPacket::PacketType) {
        diagChannel << Debug << "Got testPacket.";
        testPacket &packetC = static_cast<testPacket &>(packet);

        packetC.payload().log();
    }
}

int main() {
    debugPort.open(IODevice::WriteOnly);

    communicationPort.setDataBits(SerialPort::Data8);
    communicationPort.setStopBits(SerialPort::OneStop);
    communicationPort.setParity(SerialPort::NoParity);
    communicationPort.setBaudRate(SerialPort::Baud115200);
    communicationPort.open(SerialPort::ReadWrite);

    debugPort.write("\n\r------------------- HostComm example -------------------------\n\r");

    diagChannel.setOutputDevice(debugPort);

    // connect function that will be called when new packet will be received
    hostComm.incommingPacket.connect(proceedPacket);

    // create and run hostComm proc task
    std::thread hostCommThread([]() {
        while (1) {
            std::this_thread::sleep_for(1ms);
            hostComm.timeProc();
        }
    });

    testPacket packet;

    HostCommPacket testRequest(testPacket::Request, false);
    // hostComm.send(testRequest);

    diagChannel << Debug << "starting main loop." << endl;
    while (1) {
        std::this_thread::sleep_for(5s);
        // hostComm.ping(true);

        if (getTestRequest) {
            getTestRequest = false;
            diagChannel << Debug << "Sending test packet." << endl;
            packet.payload().setCounter(5);
            hostComm.send(packet);
        }
    }

    return 0;
}
