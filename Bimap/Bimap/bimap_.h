#pragma once

#include <set>
#include <map>

#include <string>

#include <functional>

#include <stdexcept>

namespace container {

  

    template<typename Tkey, typename Tval>
    class bimap_ final
    {
    private:
        using Map = std::map<Tkey, Tval>;
        using Setpair = std::pair<std::reference_wrapper<const Tval>, typename Map::const_iterator>;

        struct LocalLess final
        {
            const bool operator() (const Setpair& i1, const Setpair& i2) const
            {
                return (i1.first.get() < i2.first.get());
            }
        };

        using Set = std::set<Setpair, LocalLess>;

    public:
        struct NoKey final : std::exception
        {};

        struct NoVal final : std::exception
        {};

        using RetPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;

        bimap_() = default;

        bimap_(const bimap_&) = delete;
        bimap_& operator=(const bimap_&) = delete;

        bimap_(bimap_&&) = default;
        bimap_& operator=(bimap_&&) = default;

        std::size_t size() const { return map_.size(); }
        bool isEmpty() const { return map_.empty(); }

        bool checkKey(const Tkey& key) const { return map_.count(key); }
        bool checkVal(const Tval& val) const
        {
            Setpair p(std::cref(val), nullptr);
            return set_.count(p);
        }

        bool insert(const Tkey& key, const Tval& val)
        {
            const auto it = map_.insert(std::pair{ key, val });
            if (it.second) {
                if (addToSet(it.first)) {
                    return true;
                }
                map_.erase(it.first);
            }

            return false;
        }

        bool emplace(Tkey&& key, Tval&& val)
        {
            const auto it = map_.emplace(std::move(key), std::move(val));
            if (it.second) {
                if (addToSet(it.first)) {
                    return true;
                }
                map_.erase(it.first);
            }

            return false;
        }

        void keyErase(const Tkey& key)
        {
            const auto it = map_.find(key);
            if (it != map_.cend()) {
                Setpair p(std::cref(it->second), it);
                set_.erase(p);
            }
            map_.erase(it);
        }

        void valErase(const Tval& val)
        {
            Setpair p(std::cref(val), nullptr);
            const auto it = set_.find(p);
            if (it != set_.cend()) {
                typename Map::const_iterator map_it = it->second;
                map_.erase(map_it);
                set_.erase(it);
            }
        }

        RetPair keyGet(const Tkey& key) const
        {
            const auto itr = map_.find(key);
            if (itr != map_.cend()) {
                return RetPair(std::cref(itr->first), std::ref(itr->second));
            }

            throw NoKey();
        }

        RetPair valGet(const Tval& val) const
        {
            Setpair p(std::cref(val), nullptr);
            const auto it = set_.find(p);
            if (it != set_.cend()) {
                typename Map::const_iterator map_it = it->second;
                return RetPair(std::cref(map_it->first), std::ref(map_it->second));
            }

            throw NoVal();
        }

    private:
        bool addToSet(const typename Map::const_iterator it) {
            const auto set_it = set_.emplace(Setpair{ std::cref(it->second), it });
            if (!set_it.second) {
                return false;
            }

            return true;
        }

        Map map_;
        Set set_;
    };

}
