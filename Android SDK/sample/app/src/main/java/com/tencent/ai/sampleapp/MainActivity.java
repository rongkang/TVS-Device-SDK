package com.tencent.ai.sampleapp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.tencent.ai.sdk.control.SpeechManager;
import com.tencent.ai.sdk.utils.*;

/**
 * Sample主入口
 */
public class MainActivity extends Activity implements AdapterView.OnItemClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 填充Sample ListView
        String[] sampleItems = getResources().getStringArray(R.array.sample_list);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1, sampleItems);
        ListView sampleListView = (ListView)findViewById(R.id.sample_listView);
        sampleListView.setAdapter(adapter);
        sampleListView.setOnItemClickListener(this);

        // 版本信息
        ((TextView)findViewById(R.id.version_tv)).setText(com.tencent.ai.sdk.utils.BuildConfig.getVersion());
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Class sampleClass = null;
        switch (position) {
            case 0:
                sampleClass = SpeechRecognizeActivity.class;
                break;
            case 1:
                sampleClass = Text2SemanticActivity.class;
                break;
            case 2:
                sampleClass = TTSActivity.class;
                break;
            case 3:
                sampleClass = WakeupActivity.class;
                break;
        }

        if (null != sampleClass) {
            Intent intent = new Intent(this, sampleClass);
            startActivity(intent);
        }
    }
}
