//
// Created by stefan on 5/4/22.
//

#ifndef DEBEER2D_FAMILYTYPE_H
#define DEBEER2D_FAMILYTYPE_H

#include <cstddef>
#include <type_traits>

namespace Beer::internal
    {
        using FamilyID = size_t;

        template<typename...>
        class Family
        {
        private:
            inline static FamilyID m_familyCounter{};

            template<typename...>
            inline static const FamilyID m_inner = m_familyCounter++;

        public:
            template<typename... Type>
            inline static const FamilyID type = m_inner<std::decay_t<Type>...>;
        };
    }// namespace beer

#endif//DEBEER2D_FAMILYTYPE_H
