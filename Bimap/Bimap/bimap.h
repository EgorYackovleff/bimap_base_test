#pragma once


#include <set>
#include <map>

namespace container
{
	//класс bimap реализует двунаправленный map
	//bimap родительский класс для bimap_first и bimap_second - разные реализации
	//принимает: Tkey - ключ и Tval - занчение
	template<typename Tkey, typename Tval>
	class bimap //final
	{
	public:
		
		bool checkKey(const Tkey& key) const;
		bool checkVal(const Tval& val) const;

		bool insert(const Tkey& key, const Tval& val);
		bool emplace(Tkey&& key, Tval&& val);

		void keyErase(const Tkey& key);
		void valErase(const Tval& val);

		//std::pair<std::reference_wrapper<Tkey>, std::reference_wrapper<Tval>> keyGet(const Tkey& key) const;
		//std::pair<std::reference_wrapper<Tkey>, std::reference_wrapper<Tval>> valGet(const Tval& val) const;

		using RefPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;

		RefPair keyGet(const Tkey& key) const;
		RefPair valGet(const Tval& val) const;

		bimap() {
			kol_of_elem = 0;
		}

		bimap(size_t max_size_of_ring_) {
			kol_of_elem = 0;
			max_size_of_ring = max_size_of_ring_;
			isRingBimap = true;
		}

		~bimap() {
			kol_of_elem = 0;
			max_size_of_ring = 0;
			isRingBimap = false;
		}


		//возвращаем количество элементов
		std::size_t size() const final
		{
			return kol_of_elem;
		}

		//Проверка на пустоту множества
		bool isEmpty() const final
		{
			return size() == 0;
		}




	private:
		std::size_t kol_of_elem = 0;
		std::size_t max_size_of_ring;
		bool isRingBimap = 0;
	};


	

	


};


#include "bimap_first.h"
#include "bimap_second.h"


