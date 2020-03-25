// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/domain/DomainParticipantListener.hpp>
#include <dds/core/types.hpp>

namespace eprosima {
namespace fastdds {
namespace dds {

TEST(ParticipantTests, CreateDomainParticipant)
{
    DomainParticipant* participant = DomainParticipantFactory::get_instance()->create_participant(0);

    ASSERT_NE(participant, nullptr);

}

TEST(ParticipantTests, CreatePSMDomainParticipant)
{
    ::dds::domain::DomainParticipant participant = ::dds::core::null;
    participant = ::dds::domain::DomainParticipant(0, PARTICIPANT_QOS_DEFAULT);

    ASSERT_NE(participant, ::dds::core::null);

}

TEST(ParticipantTests, DomainParticipantListenerMethods)
{
    DomainParticipant* participant = DomainParticipantFactory::get_instance()->create_participant(0);

    ASSERT_EQ(participant->get_listener(), nullptr);

    DomainParticipantListener listener = DomainParticipantListener();
    participant->set_listener(&listener);

    ASSERT_EQ(&listener, participant->get_listener());

}


TEST(ParticipantTests, DomainParticipantPSMListenerMethods)
{
    ::dds::domain::DomainParticipant participant = ::dds::domain::DomainParticipant(0, PARTICIPANT_QOS_DEFAULT);

    ASSERT_EQ(participant.listener(), nullptr);

    ::dds::domain::DomainParticipantListener listener = ::dds::domain::DomainParticipantListener();
    participant.listener(&listener, ::dds::core::status::StatusMask::all());

    ASSERT_EQ(&listener, participant.listener());

}


} // namespace dds
} // namespace fastdds
} // namespace eprosima

int main(
        int argc,
        char** argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
