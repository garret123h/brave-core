/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { Reducer } from 'redux'

// Constant
import { types } from '../constants/rewards_types'
import { defaultState } from '../storage'

const rewardsReducer: Reducer<Rewards.State | undefined> = (state: Rewards.State, action) => {
  if (!state) {
    return
  }

  switch (action.type) {
    case types.IS_INITIALIZED: {
      chrome.send('brave_rewards.isInitialized')
      break
    }
    case types.GET_AUTO_CONTRIBUTE_PROPERTIES: {
      chrome.send('brave_rewards.getAutoContributeProperties')
      break
    }
    case types.ON_AUTO_CONTRIBUTE_PROPERTIES: {
      state = { ...state }
      let properties = action.payload.properties
      let ui = state.ui

      if (!properties || Object.keys(properties).length === 0) {
        break
      }

      Object.keys(properties).map((property: string) => {
        if (properties[property] !== undefined && properties[property] !== 'ui') {
          state[property] = properties[property]
        } else if (properties[property] === 'ui') {
          ui = Object.assign(ui, properties[property])
        }
      })

      state = {
        ...state,
        ui
      }

      break
    }
    case types.ON_SETTING_SAVE: {
      state = { ...state }
      const key = action.payload.key
      const value = action.payload.value
      const persist = action.payload.persist
      if (!key) {
        break
      }

      if (persist) {
        chrome.send('brave_rewards.saveSetting', [key, value.toString()])
      }

      state[key] = value
      break
    }
    case types.UPDATE_ADS_REWARDS: {
      state = { ...state }
      chrome.send('brave_rewards.updateAdRewards')
      break
    }
    case types.ON_MODAL_BACKUP_CLOSE: {
      state = { ...state }
      let ui = state.ui
      ui.walletRecoveryStatus = null
      ui.modalBackup = false
      state = {
        ...state,
        ui
      }
      break
    }
    case types.ON_MODAL_BACKUP_OPEN: {
      let ui = state.ui
      ui.modalBackup = true
      state = {
        ...state,
        ui
      }
      break
    }
    case types.ON_CLEAR_ALERT: {
      let ui = state.ui
      if (ui[action.payload.property] === undefined) {
        break
      }

      ui[action.payload.property] = null
      state = {
        ...state,
        ui
      }
      break
    }
    case types.ON_RECONCILE_STAMP: {
      state = { ...state }
      state.reconcileStamp = parseInt(action.payload.stamp, 10)
      break
    }
    case types.GET_TIP_TABLE: {
      chrome.send('brave_rewards.getRecurringTips')
      chrome.send('brave_rewards.getOneTimeTips')
      break
    }
    case types.GET_CONTRIBUTE_LIST: {
      chrome.send('brave_rewards.getContributionList')
      break
    }
    case types.GET_ADS_DATA: {
      chrome.send('brave_rewards.getAdsData')
      break
    }
    case types.ON_ADS_DATA: {
      if (!action.payload.adsData) {
        break
      }

      state = { ...state }

      if (!state.adsData) {
        state.adsData = defaultState.adsData
      }

      state.adsData.adsEnabled = action.payload.adsData.adsEnabled
      state.adsData.adsPerHour = action.payload.adsData.adsPerHour
      state.adsData.adsSubdivisionTargeting = action.payload.adsData.adsSubdivisionTargeting
      state.adsData.autoDetectedAdsSubdivisionTargeting = action.payload.adsData.autoDetectedAdsSubdivisionTargeting
      state.adsData.shouldAllowAdsSubdivisionTargeting = action.payload.adsData.shouldAllowAdsSubdivisionTargeting
      state.adsData.adsUIEnabled = action.payload.adsData.adsUIEnabled
      state.adsData.adsIsSupported = action.payload.adsData.adsIsSupported
      break
    }
    case types.GET_ADS_HISTORY: {
      chrome.send('brave_rewards.getAdsHistory')
      break
    }
    case types.ON_ADS_HISTORY: {
      if (!action.payload.adsHistory) {
        break
      }

      state = { ...state }

      if (!state.adsHistory) {
        state.adsHistory = defaultState.adsHistory
      }

      state.adsHistory = action.payload.adsHistory
      break
    }
    case types.TOGGLE_AD_THUMB_UP: {
      chrome.send('brave_rewards.toggleAdThumbUp',
                  [action.payload.uuid, action.payload.creativeSetId, action.payload.likeAction])
      break
    }
    case types.ON_TOGGLE_AD_THUMB_UP: {
      chrome.send('brave_rewards.getAdsHistory')
      break
    }
    case types.TOGGLE_AD_THUMB_DOWN: {
      chrome.send('brave_rewards.toggleAdThumbDown',
                  [action.payload.uuid, action.payload.creativeSetId, action.payload.likeAction])
      break
    }
    case types.ON_TOGGLE_AD_THUMB_DOWN: {
      chrome.send('brave_rewards.getAdsHistory')
      break
    }
    case types.TOGGLE_AD_OPT_IN_ACTION: {
      chrome.send('brave_rewards.toggleAdOptInAction',
                  [action.payload.category, action.payload.optAction])
      break
    }
    case types.ON_TOGGLE_AD_OPT_IN_ACTION: {
      chrome.send('brave_rewards.getAdsHistory')
      break
    }
    case types.TOGGLE_AD_OPT_OUT_ACTION: {
      chrome.send('brave_rewards.toggleAdOptOutAction',
                  [action.payload.category, action.payload.optAction])
      break
    }
    case types.ON_TOGGLE_AD_OPT_OUT_ACTION: {
      chrome.send('brave_rewards.getAdsHistory')
      break
    }
    case types.TOGGLE_SAVE_AD: {
      chrome.send('brave_rewards.toggleSaveAd',
                  [action.payload.uuid, action.payload.creativeSetId, action.payload.savedAd])
      break
    }
    case types.ON_TOGGLE_SAVE_AD: {
      chrome.send('brave_rewards.getAdsHistory')
      break
    }
    case types.TOGGLE_FLAG_AD: {
      chrome.send('brave_rewards.toggleFlagAd',
                  [action.payload.uuid, action.payload.creativeSetId, action.payload.flaggedAd])
      break
    }
    case types.ON_TOGGLE_FLAG_AD: {
      chrome.send('brave_rewards.getAdsHistory')
      break
    }
    case types.ON_ADS_SETTING_SAVE: {
      state = { ...state }
      const key = action.payload.key
      const value = action.payload.value
      if (key) {
        state[key] = value
        chrome.send('brave_rewards.saveAdsSetting', [key, value.toString()])

        if (key === 'adsEnabledMigrated') {
          state.enabledAdsMigrated = true
        }
      }
      break
    }
    case types.GET_TRANSACTION_HISTORY:
    case types.ON_TRANSACTION_HISTORY_CHANGED: {
      chrome.send('brave_rewards.getTransactionHistory', [])
      break
    }
    case types.ON_TRANSACTION_HISTORY: {
      if (!action.payload.data) {
        break
      }

      state = { ...state }

      if (!state.adsData) {
        state.adsData = defaultState.adsData
      }

      const data = action.payload.data
      state.adsData.adsEstimatedPendingRewards = data.adsEstimatedPendingRewards
      state.adsData.adsNextPaymentDate = data.adsNextPaymentDate
      state.adsData.adsAdNotificationsReceivedThisMonth = data.adsAdNotificationsReceivedThisMonth
      break
    }
    case types.ON_INLINE_TIP_SETTINGS_CHANGE: {
      if (!state.inlineTip) {
        state.inlineTip = {
          twitter: true,
          reddit: true,
          github: true
        }
      }

      const key = action.payload.key
      const value = action.payload.value

      if (key == null || key.length === 0 || value == null) {
        break
      }

      let inlineTip = state.inlineTip

      inlineTip[key] = value
      chrome.send('brave_rewards.setInlineTippingPlatformEnabled', [key, value.toString()])

      state = {
        ...state,
        inlineTip
      }

      break
    }
    case types.ON_ON_BOARDING_DISPLAYED: {
      let ui = state.ui

      ui.onBoardingDisplayed = true
      state = {
        ...state,
        ui
      }
      break
    }
    case types.PROCESS_REWARDS_PAGE_URL: {
      const path = action.payload.path
      const query = action.payload.query
      const ui = state.ui

      chrome.send('brave_rewards.processRewardsPageUrl', [path, query])
      ui.modalRedirect = 'show'

      state = {
        ...state,
        ui
      }
      break
    }
    case types.ON_PROCESS_REWARDS_PAGE_URL: {
      const data = action.payload.data
      const ui = state.ui

      chrome.send('brave_rewards.getExternalWallet', [data.walletType])

      // EXPIRED_TOKEN
      if (data.result === 24) {
        ui.modalRedirect = 'error'
        break
      }

      if (data.result === 25) {
        ui.modalRedirect = 'notAllowed'
        break
      }

      // NOT_FOUND
      if (data.result === 9) {
        ui.modalRedirect = 'batLimit'
        break
      }

      if (data.result !== 0) {
        ui.modalRedirect = 'error'
        break
      }

      if (data.walletType === 'uphold') {
        chrome.send('brave_rewards.fetchBalance')

        if (data.action === 'authorization') {
          const url = data.args['redirect_url']
          if (url && url.length > 0) {
            window.open(url, '_self')
          }
          ui.modalRedirect = 'hide'
          break
        }
      }

      ui.modalRedirect = 'error'

      state = {
        ...state,
        ui
      }
      break
    }
    case types.HIDE_REDIRECT_MODAL: {
      const ui = state.ui

      ui.modalRedirect = 'hide'

      state = {
        ...state,
        ui
      }
      break
    }
    case types.DISCONNECT_WALLET: {
      chrome.send('brave_rewards.disconnectWallet', [action.payload.walletType])
      break
    }
    case types.ONLY_ANON_WALLET: {
      chrome.send('brave_rewards.onlyAnonWallet')
      break
    }
    case types.ON_ONLY_ANON_WALLET: {
      const ui = state.ui

      ui.onlyAnonWallet = !!action.payload.only

      state = {
        ...state,
        ui
      }
      break
    }
    case types.DISMISS_PROMO_PROMPT: {
      const ui = state.ui
      const promoKey = action.payload.promo

      if (!ui.promosDismissed) {
        ui.promosDismissed = {}
      }

      ui.promosDismissed[promoKey] = true

      state = {
        ...state,
        ui
      }

      break
    }
    case types.GET_COUNTRY_CODE: {
      chrome.send('brave_rewards.getCountryCode')
      break
    }
    case types.ON_COUNTRY_CODE: {
      const { countryCode } = action.payload
      state = {
        ...state,
        currentCountryCode: countryCode
      }
      break
    }
    case types.ON_INITIALIZED: {
      chrome.send('brave_rewards.getReconcileStamp')
      state = {
        ...state,
        initializing: false
      }
      break
    }
    case types.COMPLETE_RESET: {
      chrome.send('brave_rewards.completeReset')
      break
    }
    case types.ON_COMPLETE_RESET: {
      if (action.payload.success) {
        return undefined
      }
      break
    }
  }

  return state
}

export default rewardsReducer
