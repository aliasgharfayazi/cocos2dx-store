package com.soomla.cocos2dx.store;

import com.soomla.store.data.StoreInfo;
import com.soomla.store.domain.NonConsumableItem;
import com.soomla.store.domain.PurchasableVirtualItem;
import com.soomla.store.domain.VirtualCategory;
import com.soomla.store.domain.VirtualItem;
import com.soomla.store.domain.virtualCurrencies.VirtualCurrency;
import com.soomla.store.domain.virtualCurrencies.VirtualCurrencyPack;
import com.soomla.store.domain.virtualGoods.UpgradeVG;
import com.soomla.store.domain.virtualGoods.VirtualGood;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import com.soomla.store.purchaseTypes.PurchaseWithMarket;
import com.soomla.store.purchaseTypes.PurchaseWithVirtualItem;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

/**
 * This bridge is used to let cocos2dx functions retrieve data from StoreInfo (through JNI).
 *
 * You can see the documentation of every function in {@link StoreInfo}
 */
public class StoreInfoBridge {

//    static String getVirtualItem(String itemId) throws VirtualItemNotFoundException{
//        VirtualItem item = StoreInfo.getVirtualItem(itemId);
//        return item.getItemId();
//    }
//
//    static String getPurchasableItem(String productId) throws VirtualItemNotFoundException{
//        PurchasableVirtualItem pvi = StoreInfo.getPurchasableItem(productId);
//        return pvi.getItemId();
//    }

    public static String getGoodFirstUpgrade(String goodItemId) throws VirtualItemNotFoundException {
        UpgradeVG vgu = StoreInfo.getGoodFirstUpgrade(goodItemId);
        return vgu.getItemId();
    }

    public static String getGoodLastUpgrade(String goodItemId) throws VirtualItemNotFoundException {
        UpgradeVG vgu = StoreInfo.getGoodLastUpgrade(goodItemId);
        return vgu.getItemId();
    }

    public static String getItemProductId(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        if (item instanceof PurchasableVirtualItem) {
            PurchasableVirtualItem pvi = (PurchasableVirtualItem) item;
            if (pvi.getPurchaseType() instanceof PurchaseWithMarket) {
                PurchaseWithMarket pwm = (PurchaseWithMarket)pvi.getPurchaseType();
                return pwm.getGoogleMarketItem().getProductId();
            }
        }
        return "";
    }

    public static String getItemName(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        return item.getName();
    }

    public static String getItemDescription(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        return item.getDescription();
    }

    public static double getItemPrice(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        if (item instanceof PurchasableVirtualItem) {
            PurchasableVirtualItem pvi = (PurchasableVirtualItem) item;
            if (pvi.getPurchaseType() instanceof PurchaseWithMarket) {
                PurchaseWithMarket pwm = (PurchaseWithMarket)pvi.getPurchaseType();
                return pwm.getGoogleMarketItem().getPrice();
            }

            if (pvi.getPurchaseType() instanceof PurchaseWithVirtualItem) {
                PurchaseWithVirtualItem pwvi = (PurchaseWithVirtualItem)pvi.getPurchaseType();
                return pwvi.getAmount();
            }
        }
        return -1;
    }

    public static JSONObject getItemByItemId(String itemId) throws VirtualItemNotFoundException {
        VirtualItem virtualItem = StoreInfo.getVirtualItem(itemId);

        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("item", virtualItem.toJSONObject());
            jsonObject.put("className", virtualItem.getClass().getSimpleName());
        } catch (JSONException e) {
            //   TODO: Implement error handling
            throw new IllegalStateException(e);
        }

        return jsonObject;
    }

    public static JSONObject getPurchasableItemWithProductId(String productId) throws VirtualItemNotFoundException {
        PurchasableVirtualItem purchasableVirtualItem = StoreInfo.getPurchasableItem(productId);

        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("item", purchasableVirtualItem.toJSONObject());
            jsonObject.put("className", purchasableVirtualItem.getClass().getSimpleName());
        } catch (JSONException e) {
            //   TODO: Implement error handling
            throw new IllegalStateException(e);
        }

        return jsonObject;
    }

    public static JSONObject getCategoryForVirtualGood(String goodItemId) throws VirtualItemNotFoundException {
        return StoreInfo.getCategory(goodItemId).toJSONObject();
    }

    public static JSONObject getFirstUpgradeForVirtualGood(String goodItemId) {
        return StoreInfo.getGoodFirstUpgrade(goodItemId).toJSONObject();
    }

    public static JSONObject getLastUpgradeForVirtualGood(String goodItemId) {
        return StoreInfo.getGoodFirstUpgrade(goodItemId).toJSONObject();
    }

    public static JSONArray getUpgradesForVirtualGood(String goodItemId) {
        List<JSONObject> jsonObjects = new ArrayList<JSONObject>();
        List<UpgradeVG> upgradeVGs = StoreInfo.getGoodUpgrades(goodItemId);
        for (UpgradeVG upgradeVG : upgradeVGs) {
            jsonObjects.add(upgradeVG.toJSONObject());
        }
        return new JSONArray(jsonObjects);
    }

    public static JSONArray getVirtualCurrencies() {
        List<JSONObject> jsonObjects = new ArrayList<JSONObject>();
        List<VirtualCurrency> virtualCurrencies = StoreInfo.getCurrencies();
        for (VirtualCurrency virtualCurrency : virtualCurrencies) {
            jsonObjects.add(virtualCurrency.toJSONObject());
        }
        return new JSONArray(jsonObjects);
    }

    public static JSONArray getVirtualGoods() {
        List<JSONObject> jsonObjects = new ArrayList<JSONObject>();
        List<VirtualGood> virtualGoods = StoreInfo.getGoods();
        for (VirtualGood virtualGood : virtualGoods) {
            jsonObjects.add(virtualGood.toJSONObject());
        }
        return new JSONArray(jsonObjects);
    }

    public static JSONArray getVirtualCurrencyPacks() {
        List<JSONObject> jsonObjects = new ArrayList<JSONObject>();
        List<VirtualCurrencyPack> virtualCurrencyPacks = StoreInfo.getCurrencyPacks();
        for (VirtualCurrencyPack virtualCurrencyPack : virtualCurrencyPacks) {
            jsonObjects.add(virtualCurrencyPack.toJSONObject());
        }
        return new JSONArray(jsonObjects);
    }

    public static JSONArray getNonConsumableItems() {
        List<JSONObject> jsonObjects = new ArrayList<JSONObject>();
        List<NonConsumableItem> nonConsumableItems = StoreInfo.getNonConsumableItems();
        for (NonConsumableItem nonConsumableItem : nonConsumableItems) {
            jsonObjects.add(nonConsumableItem.toJSONObject());
        }
        return new JSONArray(jsonObjects);
    }

    public static JSONArray getVirtualCategories() {
        List<JSONObject> jsonObjects = new ArrayList<JSONObject>();
        List<VirtualCategory> virtualCategories = StoreInfo.getCategories();
        for (VirtualCategory virtualCategory : virtualCategories) {
            jsonObjects.add(virtualCategory.toJSONObject());
        }
        return new JSONArray(jsonObjects);
    }
}
