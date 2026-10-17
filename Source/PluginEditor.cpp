#include "PluginEditor.h"

KAFSHARLevelerAudioProcessorEditor::KAFSHARLevelerAudioProcessorEditor(KAFSHARLevelerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Configure the editor before sizing it. JUCE calls resized() from setSize(),
    // so all child components must already exist and be visible at that point.
    setOpaque(true);
    setResizable(false, false);
    setWantsKeyboardFocus(false);

    titleLabel.setText("KAFSHAR  /  LEVELER", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(juce::FontOptions(23.0f, juce::Font::bold)));
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xff56d8e8));
    titleLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(titleLabel);

    configureSlider(targetSlider, targetLabel, "TARGET LEVEL");
    configureSlider(responseSlider, responseLabel, "RESPONSE");
    configureSlider(boostSlider, boostLabel, "MAX BOOST");
    configureSlider(cutSlider, cutLabel, "MAX CUT");

    targetSlider.setRange(-36.0, 0.0, 0.1);
    targetSlider.setTextValueSuffix(" dB");
    responseSlider.setRange(5.0, 500.0, 1.0);
    responseSlider.setTextValueSuffix(" ms");
    boostSlider.setRange(0.0, 24.0, 0.1);
    boostSlider.setTextValueSuffix(" dB");
    cutSlider.setRange(0.0, 24.0, 0.1);
    cutSlider.setTextValueSuffix(" dB");

    targetAttachment = std::make_unique<SliderAttachment>(audioProcessor.parameters, "targetDb", targetSlider);
    responseAttachment = std::make_unique<SliderAttachment>(audioProcessor.parameters, "responseMs", responseSlider);
    boostAttachment = std::make_unique<SliderAttachment>(audioProcessor.parameters, "maxBoostDb", boostSlider);
    cutAttachment = std::make_unique<SliderAttachment>(audioProcessor.parameters, "maxCutDb", cutSlider);

    // Keep this last: setSize() invokes resized(), which lays out the controls.
    setSize(520, 390);
    resized();
    repaint();
}

void KAFSHARLevelerAudioProcessorEditor::configureSlider(juce::Slider& slider, juce::Label& label,
                                                          const juce::String& text)
{
    label.setText(text, juce::dontSendNotification);
    label.setFont(juce::Font(juce::FontOptions(11.0f, juce::Font::bold)));
    label.setColour(juce::Label::textColourId, juce::Colour(0xffaab8c5));
    label.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 22);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xff22b8cf));
    slider.setColour(juce::Slider::thumbColourId, juce::Colour(0xffd7fbff));
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    slider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xff202b36));
    addAndMakeVisible(slider);
    slider.setEnabled(true);
}

void KAFSHARLevelerAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff10171f));

    g.setColour(juce::Colour(0xff243541));
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(8.0f), 12.0f, 1.0f);

    g.setColour(juce::Colour(0xff56d8e8));
    g.fillRoundedRectangle(18.0f, 54.0f, getWidth() - 36.0f, 2.0f, 1.0f);

    g.setFont(juce::Font(juce::FontOptions(12.0f)));
    g.setColour(juce::Colour(0xffaab8c5));
    g.drawText("AUDIO LEVEL CONTROL", 22, getHeight() - 24, getWidth() - 44, 14,
               juce::Justification::centredLeft);
}

void KAFSHARLevelerAudioProcessorEditor::resized()
{
    const int width = getWidth();
    const int height = getHeight();
    const int margin = 24;
    const int columnGap = 12;
    const int top = 72;
    const int footerHeight = 34;
    const int columnWidth = (width - (2 * margin) - columnGap) / 2;
    const int rowHeight = (height - top - footerHeight) / 2;

    targetLabel.setBounds(margin, top, columnWidth, 18);
    targetSlider.setBounds(margin - 4, top + 18, columnWidth + 8, rowHeight - 18);

    responseLabel.setBounds(margin + columnWidth + columnGap, top, columnWidth, 18);
    responseSlider.setBounds(margin + columnWidth + columnGap - 4, top + 18, columnWidth + 8, rowHeight - 18);

    const int secondRow = top + rowHeight;
    boostLabel.setBounds(margin, secondRow, columnWidth, 18);
    boostSlider.setBounds(margin - 4, secondRow + 18, columnWidth + 8, rowHeight - 18);

    cutLabel.setBounds(margin + columnWidth + columnGap, secondRow, columnWidth, 18);
    cutSlider.setBounds(margin + columnWidth + columnGap - 4, secondRow + 18, columnWidth + 8, rowHeight - 18);
}
