#include <MockTransport.h>
#include <algorithm>
#include <cstring>

using namespace std;

namespace eprosima{
namespace fastrtps{
namespace rtps{

std::vector<MockTransport*> MockTransport::mockTransportInstances;

MockTransport::MockTransport(const TransportDescriptor& descriptor):
   mockSupportedKind(descriptor.supportedKind),
   mockMaximumChannels(descriptor.maximumChannels)
{
   mockTransportInstances.push_back(this);
}

MockTransport::MockTransport():
   mockSupportedKind(DefaultKind),
   mockMaximumChannels(DefaultMaxChannels)
{
   mockTransportInstances.push_back(this);
}

MockTransport::~MockTransport()
{
   // Remove this mock from the handle vector
   mockTransportInstances.erase(std::remove(mockTransportInstances.begin(),
                                       mockTransportInstances.end(),
                                       this),
                                mockTransportInstances.end());
}

bool MockTransport::IsOutputChannelOpen(const Locator_t& locator) const
{
  return (find(mockOpenOutputChannels.begin(), mockOpenOutputChannels.end(), locator.port) != mockOpenOutputChannels.end());
}

bool MockTransport::IsInputChannelOpen(const Locator_t& locator) const
{
  return (find(mockOpenInputChannels.begin(), mockOpenInputChannels.end(), locator.port) != mockOpenInputChannels.end());
}

bool MockTransport::IsLocatorSupported(const Locator_t& locator) const
{
   return locator.kind == mockSupportedKind;
}

bool MockTransport::OpenOutputChannel(const Locator_t& locator)
{  
   mockOpenOutputChannels.push_back(locator.port);
   return true;
}

bool MockTransport::OpenInputChannel(const Locator_t& locator)
{  
   mockOpenInputChannels.push_back(locator.port);
   return true;
}

bool MockTransport::DoLocatorsMatch(const Locator_t& left, const Locator_t& right) const
{
   return left.port == right.port;
}

bool MockTransport::Send(const octet* sendBuffer, uint32_t sendBufferSize, const Locator_t& localLocator, const Locator_t& remoteLocator)
{
   std::vector<octet> sendVector;
   sendVector.assign(sendBuffer,sendBuffer + sendBufferSize);
   mockMessagesSent.push_back( { remoteLocator, localLocator, sendVector } );
   return true;
}

bool MockTransport::Receive(std::vector<octet>& receiveBuffer, const Locator_t& localChannel, Locator_t& remoteAddress)
{
   (void)localChannel;
   receiveBuffer = mockMessagesToReceive.back().data;
   remoteAddress = mockMessagesToReceive.back().origin;
   mockMessagesToReceive.pop_back();
   return true;
}

Locator_t MockTransport::RemoteToMainLocal(const Locator_t& remote) const
{
   Locator_t mainLocal(remote);
   memset(mainLocal.address, 0x00, sizeof(mainLocal.address));
   return mainLocal;
}

bool MockTransport::CloseOutputChannel(const Locator_t& locator)
{
   mockOpenOutputChannels.erase(std::remove(mockOpenOutputChannels.begin(),
                                      mockOpenOutputChannels.end(),
                                      locator.port),
                                mockOpenOutputChannels.end());
   return true;
}

bool MockTransport::CloseInputChannel(const Locator_t& locator)
{
   mockOpenInputChannels.erase(std::remove(mockOpenInputChannels.begin(),
                                      mockOpenInputChannels.end(),
                                      locator.port),
                                mockOpenInputChannels.end());
   return true;
}

} // namespace rtps
} // namespace fastrtps
} // namespace eprosima