package com.tencent.ai.sampleapp;

import android.app.Activity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.RadioGroup;

import com.tencent.ai.sampleapp.record.PcmRecorder;
import com.tencent.ai.sdk.control.SpeechManager;
import com.tencent.ai.sdk.tr.ITrListener;
import com.tencent.ai.sdk.tr.TrSession;
import com.tencent.ai.sdk.utils.ISSErrors;

import org.w3c.dom.Text;

/**
 * 语音语义识别
 * <br/>
 * 通过语音直接请求语义，包括自动检测说话停止、按住发言两种方式
 */
public class SpeechRecognizeActivity extends BaseSampleActivity implements PcmRecorder.RecordListener{

    private static final String TAG = "SpeechRecognizeActivity";

    /** 语音识别触发按钮 */
    private ImageButton mSpeechRecognizeBtn;
    /** 用于切换按钮的事件，手动和自动录音模式 */
    private AutoModeClickListener mAutoModeClickListener;
    private ManualModeTouchListener mManualModeTouchListener;

    /** SDK语音&语义识别的Session */
    private TrSession mTrSession;

    /** 录音线程 */
    private PcmRecorder mPcmRecorder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout_speech_recognize);

        // 初始化View
        initView();
        mSpeechRecognizeBtn = (ImageButton)findViewById(R.id.speech_recognize_btn);

        // 选择录音模式：默认为自动检测说话结束
        mAutoModeClickListener = new AutoModeClickListener();
        mManualModeTouchListener = new ManualModeTouchListener();
        onManualModeSet(false);

        // 初始化Session
        mTrSession = TrSession.getInstance(this, mTrListener, 0, "", "");

        // 选择识别类型, 默认语音转文字
        onRecognizeTypeSet(TrSession.ISS_TR_PARAM_VOICE_TYPE_RSP_VOICE);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if(mPcmRecorder!=null) {
            mPcmRecorder.stopThread();
        }

        if (null != mTrSession) {
            mTrSession.release();
            mTrSession = null;
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.speech_recognize_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        boolean checked = item.isChecked();
        // 自动结束录音模式
        if (id == R.id.auto_mode) {
            if (!checked) {
                item.setChecked(true);
                onManualModeSet(false);
            }
            // 手动结束录音模式
        } else if (id == R.id.manual_mode) {
            if (!checked) {
                item.setChecked(true);
                onManualModeSet(true);
            }
            // 识别类型：语音转文字
        } else if (id == R.id.speech_2_txt) {
            if (!checked) {
                item.setChecked(true);
                onRecognizeTypeSet(TrSession.ISS_TR_PARAM_VOICE_TYPE_RSP_VOICE);
            }
            // 识别类型：语音转语义
        } else if (id == R.id.speech_2_semantic) {
            if (!checked) {
                item.setChecked(true);
                onRecognizeTypeSet(TrSession.ISS_TR_PARAM_VOICE_TYPE_RSP_ALL);
            }
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onRecord(byte[] buffer, int bufferSize) {
//        printLog("录音中..." + bufferSize);
        // 收到录音数据
        if (null != mTrSession) {
            mTrSession.appendAudioData(buffer, bufferSize);
        }
    }

    /**
     * 选择录音模式
     *
     * @param manual true为手动压住发言，false为自动检测说话结束
     */
    private void onManualModeSet(boolean manual) {
        // 按键发言
        if (manual) {
            SpeechManager.getInstance().setManualMode(true);
            printLog("\n当前录音模式：按键发言，下次开启语音识别生效");
            mSpeechRecognizeBtn.setOnTouchListener(mManualModeTouchListener);
            mSpeechRecognizeBtn.setOnClickListener(null);
        } else {
            // 自动结束录音
            SpeechManager.getInstance().setManualMode(false);
            printLog("\n当前录音模式：自动检测说话结束，下次开启语音识别生效");
            mSpeechRecognizeBtn.setOnClickListener(mAutoModeClickListener);
            mSpeechRecognizeBtn.setOnTouchListener(null);
        }
    }

    /**
     * 选择识别类型
     *
     * @param type
     * @see TrSession.ISS_TR_PARAM_VOICE_TYPE_RSP_VOICE
     * @see TrSession.ISS_TR_PARAM_VOICE_TYPE_RSP_ALL
     */
    private void onRecognizeTypeSet(String type) {
        if (null == mTrSession) {
            return;
        }

        mTrSession.setParam(TrSession.ISS_TR_PARAM_VOICE_TYPE, type);
        if (type == TrSession.ISS_TR_PARAM_VOICE_TYPE_RSP_ALL) {
            printLog("\n当前识别类型：语音 -> 语义，下次开启语音识别生效");
        } else if (type == TrSession.ISS_TR_PARAM_VOICE_TYPE_RSP_VOICE) {
            printLog("\n当前识别类型：语音 -> 文本，下次开启语音识别生效");
        } else {
            printLog("\n未知类型");
        }
    }

    /**
     * 开启语音识别
     */
    private void startRecognize() {
        // 停止上次录音
        mTrSession.stop();
        stopRecord();

        String message = null;
        int id = mTrSession.start(TrSession.ISS_TR_MODE_CLOUD_REC,false);
        if (id != ISSErrors.ISS_SUCCESS) {
            message = "Tr SessionStart error,id = " + id;
            Log.e(TAG, message);
            printLog(message);
        } else {
            // 开始录音
            mPcmRecorder = new PcmRecorder(this);
            mPcmRecorder.start();

            printLog("\n开始语音识别流程：");
            printLog("开始录音");
        }
    }

    /**
     * 停止录音
     */
    private void stopRecord() {
        if(null != mPcmRecorder) {
            if (mPcmRecorder.stopThread()) {
                printLog("停止录音");
            }
        }
    }

    class AutoModeClickListener implements View.OnClickListener {

        @Override
        public void onClick(View v) {
            if (v.getId() == R.id.speech_recognize_btn) {
                startRecognize();
            }
        }
    }

    class ManualModeTouchListener implements View.OnTouchListener {

        @Override
        public boolean onTouch(View v, MotionEvent event) {
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                startRecognize();
            } else if (event.getAction() == MotionEvent.ACTION_UP) {
                if (null != mTrSession) {
                    mTrSession.endAudioData();
                }
            }

            return false;
        }
    }

    private ITrListener mTrListener = new ITrListener() {
        @Override
        public void onTrInited(boolean state, int errId) {
            String msg = "onTrInited - state : " + state + ", errId : " + errId;
            Log.i(TAG, "onTrInited - state : " + state + ", errId : " + errId);
            if (state) {
                printLog("TrSession init成功");
            } else {
                printLog("TrSession init失败, errId : " + errId);
            }
        }

        @Override
        public void onTrVoiceMsgProc(long uMsg, long wParam, String lParam) {
            String msg = null;
            Log.i(TAG, "onTrVoiceMsgProc - uMsg : " + uMsg + ", wParam : " + wParam + ", lParam : " + lParam);
            if (uMsg == TrSession.ISS_TR_MSG_SpeechStart) {
                msg = "检测到说话开始";
            } else if (uMsg == TrSession.ISS_TR_MSG_SpeechEnd) {
                msg = "检测到说话结束";
            } else if (uMsg == TrSession.ISS_TR_MSG_VoiceResult) {
                msg = "语音 -> 文本 结束，结果为：" + lParam;
                stopRecord();
            }

            if (!TextUtils.isEmpty(msg)) {
                printLog(msg);
            }
        }

        @Override
        public void onTrSemanticMsgProc(long uMsg, long wParam, int cmd, String lParam, Object extraMsg) {
            Log.i(TAG, "onTrSemanticMsgProc - uMsg : " + uMsg + ", wParam : " + wParam + ", lParam : " + lParam + ", extraMsg : " + extraMsg);
            printLog("语音 -> 语义 结束，结果为 ：");
            printLog(lParam);

            stopRecord();
        }

        @Override
        public void onTrVoiceErrMsgProc(long uMsg, long errCode, String lParam) {
            Log.i(TAG, "onTrVoiceErrMsgProc - uMsg : " + uMsg + ", errCode : " + errCode + ", lParam : " + lParam);
            printLog("语音 -> 文本 出现错误，errCode ：" + errCode + ", msg : " + lParam);

            stopRecord();
        }

        @Override
        public void onTrSemanticErrMsgProc(long uMsg, long errCode, int cmd, String lParam, Object extraMsg) {
            Log.i(TAG, "onTrSemanticErrMsgProc - uMsg : " + uMsg + ", errCode : " + errCode + ", cmd : " + cmd
                    + ", lParam : " + lParam + ", extraMsg : " + extraMsg);
            printLog("语音 -> 语义 出现错误，errCode ：" + errCode + ", cmd : " + cmd +", msg : " + lParam);

            stopRecord();
        }
    };
}
