MIDIClient.init;
MIDIIn.connectAll;

MIDIIn.control = { arg src, chan, num, val;};
MIDIIn.disconnectAll;
(
SynthDef(\sin, {
	arg triggerMode=0, amp=0, triggerModeRate=0, out=0, freq=440, pModFreq=0, pModAmp=0;
	var trigger, dust, lFOsc, pure, osc, pMod;
	// Select the Trigger Sound Mode
	dust = EnvGen.kr(Env.perc, gate: Dust.kr(triggerModeRate));
	lFOsc = SinOsc.kr(triggerModeRate / 127, mul: 0.4, add: 0.5);
	pure = 1;
	trigger = Select.kr(triggerMode, [dust, lFOsc, pure]);

	// Select the Phase Modulation
	pMod = SinOsc.ar(pModFreq, mul: pModAmp);

	// Select the Oscillator Type
	osc = SinOsc.ar(freq, phase: pMod, mul: trigger * (amp));
	Out.ar(out, osc.dup);
}).add;
)

(
MIDIFunc.cc({
	arg val, ccNum, chan;
	var setNames, setValues, amp, triggerModeRate, pModFreq, pModAmp;
	amp = val / 127;
	triggerModeRate = val / 127 * 10;
	pModFreq = val / 127 * 11000;
	pModAmp = val / 127 * 40;
	setValues = [amp, triggerModeRate, pModFreq, pModAmp];
	setNames = [\amp, \triggerModeRate, \pModFreq, \pModAmp];
	"Value: % | CC Number: % | MIDI Channel: %".format(val, ccNum, chan).postln;
	~magicChord.at(ccNum.div(4)).set(setNames.at(ccNum % 4), setValues.at(ccNum % 4));
}, (0..64), 0);

MIDIFunc.cc({arg val, ccNum, chan;
	var setNames, setDivModValues, name, value;
	[val, ccNum,chan].postln;
	setDivModValues = [1, 3, 1, 1];
	setNames = [\placeHolder, \triggerMode, \oscMode, \pModMode];
	name = setNames.at(ccNum % 4);
	~storeModeValues.put(ccNum % 4, ~storeModeValues.at(ccNum % 4) + 1);
	value = ~storeModeValues.at(ccNum % 4) % setDivModValues.at(ccNum % 4);
	[name, value].postln;
	~magicChord.at(ccNum.div(4)).set(name, value);
}, (0..64), 1);

~storeModeValues = [0, 0, 0, 0];

~magicChord = (([28, 41, 55, 69, 76, 82, 86, 91] + 12) ++ ([36, 48, 55, 60, 64, 71, 79, 84])).collect({
	arg item, i;
	Synth(\sin, [\amp, 0, \triggerModeRate, 0, \freq, item.midicps]);
})
)

4.div(4);