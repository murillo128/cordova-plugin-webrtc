/*
 * StreamingTunnel
 * Remotium Inc.
 * Copyright 2014
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


//
// StreamingTunnel is a subclass of the AsyncSocket. It only creates
// TCP scoket types; hence, listen and accept function is not supported.
// It is an asynchronous socket, so the user of this socket should connect
// to the various events declared in asyncsocket.h to receive notification
// from the StreamingTunnel socket.
//
// Example:
// StreamingTunnel.socket()->SignalConnectEvent.connect(this, &StreamingTunnel::OnConnectEvent);
// StreamingTunnel.socket()->SignalReadEvent.connect(this, &StreamingTunnel::OnReadEvent);
// StreamingTunnel.socket()->SignalWriteEvent.connect(this, &StreamingTunnel::OnWriteEvent);
// StreamingTunnel.socket()->SignalCloseEvent.connect(this, &StreamingTunnel::OnCloseEvent);
//

#ifndef STREAMING_TUNNEL_H_
#define STREAMING_TUNNEL_H_

#include <string>

#define EXPORT_TUNNEL __attribute__((visibility("default")))

namespace rtc {
    class RTCStreamingTunnelWrapper;
}

namespace Remotium {

    class EXPORT_TUNNEL RTCStreamingTunnel {
    private:
        rtc::RTCStreamingTunnelWrapper* _socket;

    public:
        typedef enum {
            OPT_DONTFRAGMENT,
            OPT_RCVBUF,      // receive buffer size
            OPT_SNDBUF,      // send buffer size
            OPT_NODELAY,     // whether Nagle algorithm is enabled
            OPT_IPV6_V6ONLY, // Whether the socket is IPv6 only.
            OPT_DSCP,        // DSCP code
        } Option;

        typedef enum {
            CS_CLOSED,
            CS_CONNECTING,
            CS_CONNECTED
        } ConnState;

        RTCStreamingTunnel();
        virtual ~RTCStreamingTunnel() {};

        virtual int Bind() { return -1; }
        virtual int Connect(const std::string& address, uint16_t port) { return -1; }
        virtual int Close() { return -1; }
        virtual int Send(const void* data, size_t len) { return -1; }
        virtual int Recv(void* data, size_t len) { return -1; }

        virtual int GetLocalAddress(std::string& hostname, int32_t& port) const { return -1; }
        virtual int GetRemoteAddress(std::string& hostname, int32_t& port) const { return -1; }

        virtual int GetOption(Option opt, int* value) { return -1; }
        virtual int SetOption(Option opt, int value) { return -1; }

        virtual void SetError(int error) { return; }
        virtual int GetError() const { return -1; }
        virtual ConnState GetState() const { return CS_CLOSED; };

        int SignalConnectEvent();
        int SignalReadEvent();
        int SignalWriteEvent();
        int SignalCloseEvent();

        //for internal use only
        rtc::RTCStreamingTunnelWrapper* socket() { return _socket; }
        void SetSocket(rtc::RTCStreamingTunnelWrapper* socket) {
            _socket = socket; }

    }; // RTCStreamingTunnel

    class EXPORT_TUNNEL RTCStreamingTunnelFactory {
    public:
        RTCStreamingTunnelFactory() {}
        virtual ~RTCStreamingTunnelFactory() {}

        virtual RTCStreamingTunnel* createNewTunnel() {
            return new RTCStreamingTunnel();
        }
    }; // RTCStreamingTunnelFactory

    void EXPORT_TUNNEL SetStreamingTunnelFactory(RTCStreamingTunnelFactory* factory);

} // namespac Remotium

#endif //STREAMING_TUNNEL_H_
