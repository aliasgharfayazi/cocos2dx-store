### v4.6.3 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.6.2...v4.6.3)

* Changes
  * Removed binaries from repo

### v4.6.2 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.6.1...v4.6.2)

* Changes
  * Added validation - not allowing null pointers in IStoreAssets

### v4.6.1 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.6.0...v4.6.1)

* New Features
  * Added OnVerificationStarted event

### v4.6.0 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.5.5...v4.6.0)

* Features
  * Added Market Purchase Deferred handling

* Changes
  * Added builder classes for initializarion params

### v4.5.5 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.5.4...v4.5.5)

* Fixes
  * StoreInventory.RemoveGoodUpgrades crash in iOS when upgrade id is null

* Changes
  * Aligned JS implementation with C++

### v4.5.4 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.5.3...v4.5.4)

* Changes
  * Removed binaries and improved build scripts

### v4.5.3 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.5.2...v4.5.3)

* Changes
  * Improved docs
  * Updated submodules

### v4.5.2 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.5.1...v4.5.2)

* New Features
  * Support Google Play verification
  * Support iOS param VERIFY_ON_ITUNES_FAILURE

* Changes
  * Support new structure of market purchase event


### v4.5.1 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.5.0...v4.5.1)

* New Features
  * Implemented new js functionality for all features

* Changes
  * Removed Consumable enum from MarketItem

* Fixes
  * Fixed an issue with androidId and iosId being set to null which prevented them from being set in the native code


### v4.5.0 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.4.1...v4.5.0)

**BREAKING API VERSION**

* Features
  * Replacing event handlers with custom events dispatched through Cocos2d-x facilities
  * Adding more information from Android in Market Purchase event (see inline documentation)

### v4.4.1 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.4.0...v4.4.1)

* Changes
  * Changing iOS bridge compilation and resulting header location

### v4.4.0 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.3.3...v4.4.0)

**BREAKING API VERSION**

* Features
  * Better integration process for Store module (see README for instructions)

### v4.3.3 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.3.2...v4.3.3)

* Changes
  * Updating Amazon plugin (v2.0.1)

### v4.3.2 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.3.1...v4.3.2)

* Features
  * Adding market refresh failed event

* Changes
  * Removing save to DB from market refresh
  * Fixes from updates submodules

### v4.3.1 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.3.0...v4.3.1)

* Features
  * Added canAfford functionality
  * Fixing [issue #153](https://github.com/soomla/cocos2dx-store/issues/153) on GitHub

### v4.3.0 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/v4.2.0...v4.3.0)

***Important***: there are some breaking changes. Read the changes carefully.

* New Features
* Work Without a Device! the code can work on other platforms (without in-app purchases testing)
* New local inventory that keeps all balances in memory so you don't need to go to the native DB. Saves JNI calls.
