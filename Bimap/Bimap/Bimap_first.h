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
		
		set_map() {}
		~set_map() {}
	};

	

	template<typename Tkey, typename Tval>
	class bimap_first : public bimap<Tkey, Tval>
	{
	public:

		

		using Base = bimap<Tkey, Tval>;

		typename std::set<typename std::map<Tkey, Tval>::const_iterator, cmp_less<Tkey, Tval>>::const_iterator find_val_iter(const Tval& val) const
		{
			if (!isEmpty()) {
				auto it_ = Set_map.set_bimap.begin();
				bool flag = false;
				int left = 0; int right = size() - 1;
				int centr; int int_iter = 0;
				while ((left <= right) && (flag != true))
				{
					centr = (left + right) / 2;

					//it_ +=ы + 1; // как сделаьб?
					for (int_iter; int_iter < centr; int_iter++) it_++;
					for (int_iter; int_iter > centr; int_iter--) it_--;

					// Set_map.set_bimap.begin() + 1;
					auto val__in_iter = std::pair<Tkey, Tval>(**it_).second;
					if (val == val__in_iter) flag = true;
					else
					{
						if (val__in_iter > val) right = centr - 1;
						else left = centr + 1;

					}
				}
				if (flag) return it_;
				else return Set_map.set_bimap.end();

			}
		}


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
			////if (!isEmpty()) {
			////	//auto it_ = Set_map.set_bimap.begin();
			////	///*auto a = *it_;
			////	//auto b = *a;
			////	//auto c = **it_;*/
			////	//
			////	//for ( it_ ; it_ != Set_map.set_bimap.end() ; it_++)
			////	//{
			////	//	if (val == std::pair<Tkey, Tval>(**it_).second) return true;+		std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,std::string>>>>>>>
			////	//}// if (val == std::pair<Tkey, Tval>(**it_).second) return true;+		std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,std::string>>>>>>>
			////}
			////auto a = find_val_iter(val);
			//auto a = find_val_iter(val);
			//auto b = Set_map.set_bimap.end();
			if (!isEmpty()) return find_val_iter(val) != Set_map.set_bimap.end();
			return false;
		
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
		
		void keyErase(const Tkey& key) //const
		{
			if (checkKey(key) != 0) {
				Tval val = Set_map.map_Key_Val[key];
				
				Set_map.set_bimap.erase(find_val_iter(val));

				Set_map.map_Key_Val.erase(Set_map.map_Key_Val.find(key));
				Base::kol_of_elem--; 
			}
			else
			{
				throw std::bad_alloc();
			}
		}
		
		void valErase(const Tval& val)
		{
			if (checkVal(val) != 0) {
				auto iter_to_val = find_val_iter(val);
				auto pair_ = **iter_to_val;
				auto key = pair_.first;
				Set_map.set_bimap.erase(iter_to_val);
				Set_map.map_Key_Val.erase(Set_map.map_Key_Val.find(key));

				Base::kol_of_elem--;

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

				return std::make_pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>(Set_map.map_Key_Val.find(key)->first, Set_map.map_Key_Val[key]);
			}
			else
			{
				throw std::bad_alloc();
			}

		}




		RefPair valGet(const Tval& val)
		{
			if (checkVal(val) != 0) {
				auto a = *find_val_iter(val);
				return std::make_pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>(a->first, a->second);
				
			}
			else
			{
				throw std::bad_alloc();
			}
		}



	private:

		set_map <Tkey, Tval> Set_map;
		//Bimap_2X<Tkey, Tval> bimap_2x;
		
		

	};

}