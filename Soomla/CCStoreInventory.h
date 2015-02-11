/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */


#ifndef __CCStoreInventory_H_
#define __CCStoreInventory_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCVirtualGood.h"
#include "CCUpgradeVG.h"
#include "CCVirtualCurrency.h"
#include "CCEquippableVG.h"

namespace soomla {
	/** @class CCStoreInventory
		@brief An interface to the native StoreInventory class.

		An interface to the native StoreInventory class, use this class to
		access the native StoreInventory functionality.
	 */
    class CCStoreInventory: public cocos2d::CCObject {
    public:

        /**
         This class is singleton, use this function to access it.
		 */
        static CCStoreInventory* sharedStoreInventory();

        CCStoreInventory() : mLocalItemBalances(NULL), mLocalUpgrades(NULL),
            mLocalEquippedGoods(NULL) {}
        
        virtual bool init();

        virtual ~CCStoreInventory(void);
        
        /**
         Checks if there is enough funds to afford `itemId`.
         @param itemId id of item to be checked
         @param error A `CCError` for error checking.
         @return True if there are enough funds to afford the virtual item 
         with the given item id
         */
        bool canAfford(const char *itemId, CCError **error = NULL);

		/**
         Buys the item with the given `itemId`.
         @param itemId The id of the item to be purchased.
         @param error A `CCError` for error checking.
		 */
        void buyItem(const char *itemId, CCError **error = NULL);

		/**
         Buys the item with the given `itemId`.
         @param itemId The id of the item to be purchased.
         @param payload Payload.
         @param error A `CCError` for error checking.
		 */
        void buyItem(const char *itemId, const char *payload, CCError **error = NULL);

		/**
         Retrieves the balance of the virtual item with the given `itemId`.
         @param itemId The id of the virtual item to be fetched - must be of
         `CCVirtualCurrency`, `CCSingleUseVG`, `CCLifetimeVG`, `CCEquippableVG`.
         @param error A `CCError` for error checking.
         @return The balance of the virtual item with the given `itemId`.
		*/
        int getItemBalance(const char *itemId, CCError **error = NULL);

		/**
         Gives your user the given amount of the virtual item with the given
         `itemId`.
         For example, when your user plays your game for the first time you GIVE
         him/her 1000 gems.
         NOTE: This action is different than `buy` -
         You use `give` to give your user something for free.
         You use `buy` to give your user something and get something in return.
         @param amount The amount of the item to be given.
         @param itemId The id of the virtual item to be given.
         @param error A `CCError`for error checking.
         */
		void giveItem(const char *itemId, int amount, CCError **error = NULL);

		/**
         Takes from your user the given amount of the virtual item with the
         given `itemId`.
         For example, when you want to downgrade a virtual good, you take the
         upgrade.
         @param amount The amount of the item to be given.
         @param itemId The id of the virtual item to be taken.
         @param error A `CCError` for error checking.
         */
        void takeItem(const char *itemId, int amount, CCError **error = NULL);

		/**
         Equips the virtual good with the given `goodItemId`.
         Equipping means that the user decides to currently use a specific
         virtual good. For more details and examples see `CCEquippableVG`.
         @param itemId The id of the virtual good to be equipped. Id MUST
                be of a `CCEquippableVG`.
         @param error A `CCError` for error checking.
		*/
        void equipVirtualGood(const char *itemId, CCError **error = NULL);

		/**
         Unequips the virtual good with the given `goodItemId`. Unequipping
         means that the user decides to stop using the virtual good he/she is
         currently using. For more details and examples see `CCEquippableVG`.
         @param itemId The id of the virtual good to be unequipped. Id MUST
                be of a `CCEquippableVG`.
         @param error A `CCError` for error checking.
         */
		void unEquipVirtualGood(const char *itemId, CCError **error = NULL);

		/**
         Checks if the virtual good with the given `goodItemId` is equipped
         (currently being used).
         @param itemId The id of the virtual good to check on. Id MUST be of
                an `EquippableVG`.
         @param error A `CCError` for error checking.
         @return True if the virtual good with the given id is equipped, false
                otherwise.
         */
        bool isVirtualGoodEquipped(const char *itemId, CCError **error = NULL);

		/**
         Retrieves the upgrade level of the virtual good with the given
         `goodItemId`.
         For Example:
         Let's say there's a strength attribute to one of the characters in your
         game and you provide your users with the ability to upgrade that
         strength on a scale of 1-3.
         This is what you've created:
         1. `CCSingleUseVG` for "strength"
         2. `CCUpgradeVG` for strength 'level 1'
         3. `CCUpgradeVG` for strength 'level 2'
         4. `CCUpgradeVG` for strength 'level 3'
         In the example, this function will retrieve the upgrade level for
         "strength" (1, 2, or 3).
         @param goodItemId The id of the virtual good whose upgrade level we
                want to know. The `goodItemId` can be of any `CCVirtualGood`.
         @param error A `CCError` for error checking.
         @return The upgrade level.
         */
        int getGoodUpgradeLevel(const char *goodItemId, CCError **error = NULL);

		/**
         Retrieves the item id of the current upgrade of the virtual good with
         the given `goodItemId`.
         @param goodItemId Id of the virtual good whose upgrade id we want to
                know. The `goodItemId` can be of any `CCVirtualGood`.
         @param error A `CCError` for error checking.
         @return The upgrade id if exists, or empty string otherwise.
         */
		std::string getGoodCurrentUpgrade(const char *goodItemId, CCError **error = NULL);

		/**
         Upgrades the virtual good with the given `goodItemId` by doing the
         following:
         1. Checks if the good is currently upgraded or if this is the first
         time being upgraded.
         2. If the good is currently upgraded, upgrades to the next upgrade in
         the series, or in other words, buys the next upgrade. In case there
         are no more upgrades available (meaning the current upgrade is the last
         available) the function returns.
         3. If the good has never been upgraded before, the function upgrades it
         to the first available upgrade, or in other words, buy()s the first
         upgrade in the series.
         @param goodItemId The id of the virtual good to be upgraded. The
                `upgradeItemId` can be of any `CCUpgradeVG`.
         @param error A `CCError` for error checking.
         */
        void upgradeGood(const char *goodItemId, CCError **error = NULL);

		/**
         Removes all upgrades from the virtual good with the given `goodItemId`.
         @param goodItemId The id of the virtual good we want to remove all
                upgrades from. The `upgradeItemId` can be of any `UpgradeVG`.
         @param error A `CCError` for error checking.
         */
		void removeGoodUpgrades(const char *goodItemId, CCError **error = NULL);
        
        /**
         This function refreshes a local set of objects that will hold your user's balances in memory for quick
         and more efficient fetching for your game UI.
         This way, we save many JNI or static calls to native platforms.
         
         NOTE: You don't need to call this function as it's automatically called when the game initializes.
         NOTE: This is less useful when you work in editor.
         */
        void refreshLocalInventory();
        
        /** Internal methods **/
        
        void refreshOnGoodUpgrade(CCVirtualGood *vg, CCUpgradeVG *uvg);
        void refreshOnGoodEquipped(CCEquippableVG *equippable);
        void refreshOnGoodUnEquipped(CCEquippableVG *equippable);
        void refreshOnCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);
        void refreshOnGoodBalanceChanged(CCVirtualGood *good, int balance, int amountAdded);
        void updateLocalBalance(const char *itemId, int balance);
        
        void handle__REFLECTION_REFRESH_LOCAL_INVENTORY(cocos2d::CCDictionary *paramaters);
    private:
        cocos2d::CCDictionary *mLocalItemBalances;
        cocos2d::CCDictionary *mLocalUpgrades;
        cocos2d::CCSet *mLocalEquippedGoods;
        
        class CCLocalUpgrade : public cocos2d::CCObject {
            CC_SYNTHESIZE_RETAIN(cocos2d::CCInteger *, mLevel, Level);
            CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, mItemId, ItemId);
        public:
            static CCLocalUpgrade *create();
            CCLocalUpgrade() : mLevel(NULL), mItemId(NULL) {}
        };
    };
};

#endif //__CCStoreInventory_H_
