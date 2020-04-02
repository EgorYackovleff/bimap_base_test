#pragma once
#include "bimap.h"



namespace container
{


	template<typename Tkey, typename Tval>
	struct Bimap_2X
	{
		std::map <Tkey, Tval> map_Key_Val;
		std::map <Tval, Tkey> map_Val_Key;
		//Bimap_2X() {}
		//~Bimap_2X() {}
	};


	template<typename Tkey, typename Tval>
	class bimap_second : public bimap<Tkey, Tval>
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



		bimap_second()
		{
			Base::kol_of_elem = 0;
			Base::isRingBimap = false;
		}

		bool checkKey(const Tkey& key) const
		{
			return bimap_2x.map_Key_Val.count(key);
		}

		bool checkVal(const Tval& val) const
		{
			return bimap_2x.map_Val_Key.count(val);
		}

		bool insert(const Tkey& key, const Tval& val)
		{
			if (checkKey(key) == 0 && checkVal(val) == 0) {
				bimap_2x.map_Key_Val.insert(std::pair<Tkey, Tval> (key, val));
				bimap_2x.map_Val_Key.insert(std::pair<Tval, Tkey>(val, key));
				Base::kol_of_elem++ ; //kbimap_2x.map_Key_Val.size()
				return true;
			}
			else return false;
		}

		bool emplace(Tkey&& key, Tval&& val)
		{
			if (checkKey(key) == 0 && checkVal(val) == 0) {
				bimap_2x.map_Key_Val.emplace(key, val);
				bimap_2x.map_Val_Key.emplace(val, key);
				Base::kol_of_elem++; //kbimap_2x.map_Key_Val.size()
				return true;
			}
			else return false;
		}

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
		}


		using RefPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;

		RefPair keyGet(const Tkey& key) 
		{

			if (checkKey(key) != 0) {
				
				return std::make_pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>(bimap_2x.map_Key_Val.find(key)->first, bimap_2x.map_Key_Val[key]);
			}
			else
			{
				throw std::bad_alloc();
			}

		}

		


		RefPair valGet(const Tval& val)
		{
			if (checkVal(val) != 0) {
				auto a = std::make_pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>(bimap_2x.map_Val_Key[val], bimap_2x.map_Val_Key.find(val)->first);
				return a;
			}
			else
			{
				throw std::bad_alloc();
			}
		}



	private:

		Bimap_2X<Tkey, Tval> bimap_2x;
		
	
	};

}


