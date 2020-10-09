/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/feature_list.h"
#include "base/path_service.h"
#include "base/test/scoped_feature_list.h"
#include "brave/app/brave_command_line_helper.h"
#include "brave/common/brave_paths.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "content/browser/native_file_system/file_system_chooser_test_helpers.h"
#include "content/public/common/content_features.h"
#include "content/public/common/content_switches.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "net/dns/mock_host_resolver.h"
#include "net/test/embedded_test_server/embedded_test_server.h"
#include "third_party/blink/public/common/features.h"
#include "ui/shell_dialogs/select_file_dialog.h"
#include "ui/shell_dialogs/select_file_dialog_factory.h"
#include "url/gurl.h"

class BlinkAPIBrowserTest : public InProcessBrowserTest {
 public:
  BlinkAPIBrowserTest() : https_server_(net::EmbeddedTestServer::TYPE_HTTPS) {
    brave::RegisterPathProvider();
    base::FilePath test_data_dir;
    base::PathService::Get(brave::DIR_TEST_DATA, &test_data_dir);
    https_server_.SetSSLConfig(net::EmbeddedTestServer::CERT_OK);
    https_server_.ServeFilesFromDirectory(test_data_dir);
    EXPECT_TRUE(https_server_.Start());
  }

  ~BlinkAPIBrowserTest() override = default;

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    host_resolver()->AddRule("*", "127.0.0.1");
  }

 protected:
  net::EmbeddedTestServer https_server_;
};

// Test positive case: NativeFileSystem API works when enabled via its feature.
class NativeFileSystemAPIBrowserTest : public BlinkAPIBrowserTest {
 public:
  NativeFileSystemAPIBrowserTest() {}

   void SetUp() override {
    scoped_feature_list_.InitAndEnableFeature(
        blink::features::kNativeFileSystemAPI);
    BlinkAPIBrowserTest::SetUp();
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    // blink::features::kNativeFileSystemAPI feature is enabled by default but
    // we disable it in BraveContentRendererClient::
    // SetRuntimeFeaturesDefaultsBeforeBlinkInitialization, so this will enable
    // it again. See check for command line override in
    // SetCustomizedRuntimeFeaturesFromCombinedArgs (runtime_features.cc).
    //BraveCommandLineHelper brave_command_line(command_line);
    //brave_command_line.AppendFeatures(
    //    {blink::features::kNativeFileSystemAPI.name}, {});
  }

 protected:
  base::test::ScopedFeatureList scoped_feature_list_;
};

IN_PROC_BROWSER_TEST_F(NativeFileSystemAPIBrowserTest, FilePicker) {
  EXPECT_TRUE(
      base::FeatureList::IsEnabled(blink::features::kNativeFileSystemAPI));
  ui::SelectFileDialog::SetFactory(
      new content::CancellingSelectFileDialogFactory);
  const GURL url = https_server_.GetURL("/simple.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  content::RenderFrameHost* rfh = contents->GetMainFrame();

  auto result = content::EvalJs(rfh, "self.showOpenFilePicker()");
  EXPECT_TRUE(result.error.find("aborted") != std::string::npos)
      << result.error;
}

// Test negative case: NativeFileSystem API doesn't work when its feature is not
// explicitly enabled.
class NativeFileSystemAPIDisabledBrowserTest : public BlinkAPIBrowserTest {
 public:
  NativeFileSystemAPIDisabledBrowserTest() {}
};

IN_PROC_BROWSER_TEST_F(NativeFileSystemAPIDisabledBrowserTest, FilePicker) {
  ui::SelectFileDialog::SetFactory(
      new content::CancellingSelectFileDialogFactory);
  const GURL url = https_server_.GetURL("/simple.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  content::RenderFrameHost* rfh = contents->GetMainFrame();

  auto result = content::EvalJs(rfh, "self.showOpenFilePicker()");
  EXPECT_TRUE(result.error.find("self.showOpenFilePicker is not a function") !=
              std::string::npos)
      << result.error;
}

/* For Cr87
IN_PROC_BROWSER_TEST_F(DirectSocketsAPIDisabledBrowserTest, OpenTCPSocket) {
  const GURL url = https_server_.GetURL("/simple.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  content::RenderFrameHost* rfh = contents->GetMainFrame();

  auto result = content::EvalJs(
      rfh,
      "navigator.openTCPSocket({remoteAddress: '127.0.0.1', remotePort: 0})");
  EXPECT_TRUE(result.error.find("navigator.openTCPSocket is not a function") !=
              std::string::npos)
      << result.error;
}
*/

// Test positive case: DigitalGoods API works when enabled via experimental
// features.
class DigitalGoodsAPIBrowserTest : public BlinkAPIBrowserTest {
 public:
  DigitalGoodsAPIBrowserTest() {}

  void SetUpCommandLine(base::CommandLine* command_line) override {
    BlinkAPIBrowserTest::SetUpCommandLine(command_line);
    command_line->AppendSwitch(
        switches::kEnableExperimentalWebPlatformFeatures);
  }
};

IN_PROC_BROWSER_TEST_F(DigitalGoodsAPIBrowserTest, DigitalGoods) {
  const GURL url = https_server_.GetURL("/simple.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  content::RenderFrameHost* rfh = contents->GetMainFrame();

  auto result = content::EvalJs(
      rfh, "window.getDigitalGoodsService()");
  EXPECT_TRUE(
      result.error.find("Failed to execute 'getDigitalGoodsService' on "
                        "'Window': 1 argument required, but only 0 present.") !=
      std::string::npos)
      << result.error;
}

// Test negative case: DigitalGoods API doesn't work when experimental features
// aren't enabled.
class DigitalGoodsAPIDisabledBrowserTest : public BlinkAPIBrowserTest {
 public:
  DigitalGoodsAPIDisabledBrowserTest() {}
};

IN_PROC_BROWSER_TEST_F(DigitalGoodsAPIDisabledBrowserTest, DigitalGoods) {
  const GURL url = https_server_.GetURL("/simple.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  content::RenderFrameHost* rfh = contents->GetMainFrame();

  auto result = content::EvalJs(rfh, "Window.getDigitalGoodsService()");
  EXPECT_TRUE(
      result.error.find("Window.getDigitalGoodsService is not a function") !=
      std::string::npos)
      << result.error;
}
