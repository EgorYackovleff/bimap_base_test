#pragma once
#include "bimap.h"


namespace container
{


	template<typename Tkey, typename Tval>
	struct cmp_less {
		template<typename I>
		bool operator()(const I& lh, const I& rh) const { return lh->second < rh->second; }

	};

	template<typename Tkey, typename Tval>
	struct set_map
	{
		std::map <Tkey, Tval> map_Key_Val;

		std::set<typename std::map<Tkey, Tval>::const_iterator, cmp_less<Tkey, Tval>> set_bimap;

		//std::set < std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<int const, std::string>>>>> set_bimap;
		
		set_map() {}
		~set_map() {}
	};

	

	template<typename Tkey, typename Tval>
	class bimap_first : public bimap<Tkey, Tval>
	{
	public:

		

		using Base = bimap<Tkey, Tval>;


		//возвращаем количество элементов
		std::size_t size() const
		{
			return Base::kol_of_elem;
		}

		//Проверка на пустоту множества
		bool isEmpty() const
		{
			return size() == 0;
		}



		bimap_first()
		{
			Base::kol_of_elem = 0;
			Base::isRingBimap = false;
		}

		bool checkKey(const Tkey& key) const
		{
			return Set_map.map_Key_Val.count(key);
		}

		bool checkVal(const Tval& val) const
		{
			/*auto a = Set_map.set_bimap.find()
			auto b = Set_map.set_bimap.end();*/

			
			return 1;

		}


		bool insert(const Tkey& key, const Tval& val)
		{
			if (checkKey(key) == 0 && checkVal(val) == 0) {
				Set_map.map_Key_Val.insert(std::pair<Tkey, Tval>(key, val));
				Set_map.set_bimap.insert(Set_map.map_Key_Val.find(key));


				Base::kol_of_elem++; //kbimap_2x.map_Key_Val.size()
				return true;
			}
			else return false;
		}




		bool emplace(Tkey&& key, Tval&& val) 
		{
			if (checkKey(key) == 0 && checkVal(val) == 0) {
				Set_map.map_Key_Val.emplace(key, val);
				Set_map.set_bimap.emplace(Set_map.map_Key_Val.find(key));
				Base::kol_of_elem++; 
				return true;
			}
			else return false;
		}
		/*
		void keyErase(const Tkey& key)
		{
			if (checkKey(key) != 0) {
				bimap_2x.map_Val_Key.erase(bimap_2x.map_Key_Val[key]);
				bimap_2x.map_Key_Val.erase(key);
				Base::kol_of_elem--; //kbimap_2x.map_Key_Val.size()
			}
			else
			{
				throw std::bad_alloc();
			}
		}

		void valErase(const Tval& val)
		{
			if (checkVal(val) != 0) {
				bimap_2x.map_Key_Val.erase(bimap_2x.map_Val_Key[val]);
				bimap_2x.map_Val_Key.erase(val);
				Base::kol_of_elem--; //kbimap_2x.map_Key_Val.size()
			}
			else
			{
				throw std::bad_alloc();
			}
		}*/


		using RefPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;

		RefPair keyGet(const Tkey& key)
		{

			if (checkKey(key) != 0) {

				return std::make_pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>(Set_map.map_Key_Val.find(key)->first, Set_map.map_Key_Val[key]);
			}
			else
			{
				throw std::bad_alloc();
			}

		}




		/*RefPair valGet(const Tval& val)
		{
			if (checkVal(val) != 0) {
				auto a = std::make_pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>(bimap_2x.map_Val_Key[val], bimap_2x.map_Val_Key.find(val)->first);
				return a;
			}
			else
			{
				throw std::bad_alloc();
			}
		}*/



	private:

		set_map <Tkey, Tval> Set_map;
		//Bimap_2X<Tkey, Tval> bimap_2x;
		
		

	};

}