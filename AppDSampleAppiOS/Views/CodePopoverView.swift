//
//  CodePopoverView.swift
//  AppDSampleAppiOS

import Foundation
import SwiftUI
import ADEUMInstrumentation

final class CodePopoverViewController: UIHostingController<CodePopoverView> {
    
    var snippet: String = "" {
        didSet {
            rootView.snippet = snippet
        }
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder, rootView: CodePopoverView())
        rootView.dismiss = dismiss
        rootView.snippet = snippet
    }
    
    @objc func dismiss() {
        let tracker = ADEumInstrumentation.beginCall(self, selector: #selector(self.dismiss(animated:completion:)))
        dismiss(animated: true, completion: nil)
        ADEumInstrumentation.endCall(tracker)
    }
}

struct CodePopoverView: View {
    
    var dismiss: (() -> Void)?

    @Environment(\.presentationMode) var mode

    var snippet =
    """
    /**
     This shows the instrumentation code for the feature. In many cases, no code is needed.
    **/
    """
    
    var body: some View {
        VStack {
            Button(action: {
                if let dismiss: (() -> Void) = self.dismiss {
                    dismiss()
                }
            }, label: {
                Text("Dismiss")
            }).padding()
            Spacer()
            CodeSnippetView(text: snippet)
            Spacer()
            Button(action: {
                UIPasteboard.general.string = self.snippet
            }, label: {
                Text("Copy")
            }).padding()
        }
    }
}


struct CodePopoverView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Placeholder Content")
    }
}
