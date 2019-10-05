/*
 * Copyright 2010, Object Management Group, Inc.
 * Copyright 2019, Proyectos y Sistemas de Mantenimiento SL (eProsima).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef OMG_DDS_CORE_XTYPES_STRUCT_TYPE_HPP_
#define OMG_DDS_CORE_XTYPES_STRUCT_TYPE_HPP_

#include <dds/core/xtypes/AggregationType.hpp>
#include <dds/core/xtypes/StructMember.hpp>

#include <string>
#include <map>
#include <vector>

namespace dds {
namespace core {
namespace xtypes {

class StructType : public AggregationType<StructMember>
{
public:
    StructType(
            const std::string& name)
        : AggregationType(name, TypeKind::STRUCTURE_TYPE)
    {}

    StructType(
            const StructType& other)
        : AggregationType(other)
        , parent_(other.parent_ != nullptr ? other.parent_->clone() : nullptr)
        , memory_size_(other.memory_size_)
     {}

    bool has_parent() const { return parent_ == nullptr; }
    const DynamicType& parent() const { return *parent_; }

    StructType& add_member(const StructMember& member)
    {
        StructMember& inner = insert_member(member.name(), member);
        inner.offset_ = memory_size_;
        memory_size_ += inner.type().memory_size();
        return *this;
    }

    virtual size_t memory_size() const
    {
        return memory_size_;
    }

    virtual DynamicType* clone() const
    {
        return new StructType(*this);
    }

private:
    std::unique_ptr<DynamicType> parent_;
    size_t memory_size_;
};

} //namespace xtypes
} //namespace core
} //namespace dds

#endif //OMG_DDS_CORE_XTYPES_STRUCT_TYPE_HPP_