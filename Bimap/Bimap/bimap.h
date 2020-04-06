#pragma once


#include <set>
#include <map>
#include <iostream>
#include "bimap_.h"

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


		using RefPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;

		RefPair keyGet(const Tkey& key) const;
		RefPair valGet(const Tval& val) const;

		bimap() {
			//kol_of_elem = 0;
		}

		bimap(size_t max_size_of_ring_) {
			kol_of_elem = 0;
			max_size_of_deque = max_size_of_ring_;
			isRingBimap = true;
		}

		~bimap() {
			kol_of_elem = 0;
			max_size_of_deque = 0;
			isRingBimap = false;
		}


		//возвращаем количество элементов
		std::size_t size() const
		{
			return kol_of_elem;
		}

		//Проверка на пустоту множества
		bool isEmpty() const
		{
			return size() == 0;
		}

		


	protected:
		std::size_t kol_of_elem = 0;
		std::size_t max_size_of_deque;
		bool isRingBimap = 0;
		


	};

	

};


//namespace container
//{
//
//	template<typename Tkey, typename Tval>
//	class bimap_second : public bimap<Tkey, Tval>
//	{
//
//		bimap_second ()
//		{
//			//kol_of_elem = 0;
//			kol = 0;
//		}
//		
//		bool checkKey(const Tkey& key) const
//		{
//			return bimap_2x.map_Key_Val.count(key);
//		}
//
//		bool checkVal(const Tval& val) const
//		{
//			return bimap_2x.map_Val_Key.count(val);
//		}
//
//		bool insert(const Tkey& key, const Tval& val)
//		{
//			if (checkKey(key) == 0) {
//				bimap_2x.map_Key_Val.insert(key, val);
//				bimap_2x.map_Val_Key.insert(val, key);
//				return true;
//			}
//			else return false;
//		}
//
//		bool emplace(Tkey&& key, Tval&& val)
//		{
//			if (checkKey(key) == 0) {
//				bimap_2x.map_Key_Val.emplace(key, val);
//				bimap_2x.map_Val_Key.emplace(val, key);
//				return true;
//			}
//			else return false;
//		}
//
//		void keyErase(const Tkey& key)
//		{
//			if (checkKey(key) != 0) {
//				bimap_2x.map_Val_Key.erase(bimap_2x.map_Key_Val[key]);
//				bimap_2x.map_Key_Val.erase(key);
//			}
//		}
//
//		void valErase(const Tval& val)
//		{
//			if (checkVal(val) != 0) {
//				bimap_2x.map_Key_Val.erase(bimap_2x.map_Val_Key[val]);
//				bimap_2x.map_Val_Key.erase(val);
//			}
//		}
//
//
//		using RefPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;
//
//		RefPair keyGet(const Tkey& key) const
//		{
//
//			if (checkKey(key) != 0) {
//				
//				return std::make_pair(std::reference_wrapper<const Tkey>(key), std::reference_wrapper<const TVal>(bimap_2x.map_Key_Val[key]));
//			}
//
//		}
//
//
//
//		RefPair valGet(const Tval& val) const
//		{
//			if (checkVal(val) != 0) {
//				return std::make_pair(std::reference_wrapper<const Tkey>(bimap_2x.map_Val_Key[val]), std::reference_wrapper<const TVal>(val));
//			}
//		}
//
//
//
//	private:
//		
//		template<typename Tkey, typename Tval>
//		union Bimap_2X
//		{
//			std::map <Tkey, Tval> map_Key_Val;
//			std::map <Tval, Tkey> map_Val_Key;
//		}; 
//
//		Bimap_2X bimap_2x;
//
//
//		int kol;
//		//Bimap_2X bimap_2x;
//	};
//
//
//
//
//
//
//}









#include "bimap_first.h"
#include "bimap_second.h"


