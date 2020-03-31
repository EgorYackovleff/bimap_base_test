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
		bimap_second()
		{
			
			//kol = 0;
			kol_of_elem = 0;
			isRingBimap = false;
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
			if (checkKey(key) == 0) {
				bimap_2x.map_Key_Val.insert(key, val);
				bimap_2x.map_Val_Key.insert(val, key);
				kol_of_elem = bimap_2x.map_Key_Val.size(); //kol_of_elem++
				return true;
			}
			else return false;
		}

		bool emplace(Tkey&& key, Tval&& val)
		{
			if (checkKey(key) == 0) {
				bimap_2x.map_Key_Val.emplace(key, val);
				bimap_2x.map_Val_Key.emplace(val, key);
				kol_of_elem = bimap_2x.map_Key_Val.size(); //kol_of_elem++
				return true;
			}
			else return false;
		}

		void keyErase(const Tkey& key)
		{
			if (checkKey(key) != 0) {
				bimap_2x.map_Val_Key.erase(bimap_2x.map_Key_Val[key]);
				bimap_2x.map_Key_Val.erase(key);
				kol_of_elem = bimap_2x.map_Key_Val.size(); //kol_of_elem--
			}
		}

		void valErase(const Tval& val)
		{
			if (checkVal(val) != 0) {
				bimap_2x.map_Key_Val.erase(bimap_2x.map_Val_Key[val]);
				bimap_2x.map_Val_Key.erase(val);
				kol_of_elem = bimap_2x.map_Key_Val.size(); //kol_of_elem--
			}
		}


		using RefPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;

		RefPair keyGet(const Tkey& key) const
		{

			if (checkKey(key) != 0) {

				return std::make_pair(std::reference_wrapper<const Tkey>(key), std::reference_wrapper<const Tval>(bimap_2x.map_Key_Val[key]));

			}

		}



		RefPair valGet(const Tval& val) const
		{
			if (checkVal(val) != 0) {
				return std::make_pair(std::reference_wrapper<const Tkey>(bimap_2x.map_Val_Key[val]), std::reference_wrapper<const Tval>(val));
			}
		}



	private:

		Bimap_2X<Tkey, Tval> bimap_2x;
		
		std::size_t kol_of_elem = 0;
		std::size_t max_size_of_ring;
		bool isRingBimap = 0;
	
	};

}


